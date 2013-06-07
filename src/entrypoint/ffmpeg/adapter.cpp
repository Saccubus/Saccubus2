/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <signal.h>
#define SACC_DLL_EXPORT 1
#include "saccubus_adapter.h"
#include "../../saccubus/Saccubus.h"

namespace ffmpeg {

void errorwait(bool exit=false)
{
	std::cout << "[Saccubus FFmpeg Adapter] An error has occurred. Press [ENTER] to continue." << std::endl;
	std::getchar();
	if (exit){
		std::exit(-1);
	}
}

class FFmpegAdapter : public saccubus::Adapter
{
	DEFINE_MEMBER(private, private, saccubus::Saccubus*, parent);
private:
	SaccToolBox* const box;
private:
	SDL_Window* window;
	SDL_Surface* windowSurface;
public:
	FFmpegAdapter(saccubus::Saccubus* const parent, SaccToolBox* const box)
	:box(box)
	,window(0)
	,windowSurface(0)
	{
		this->parent(parent);
	}
	virtual ~FFmpegAdapter()
	{
		if(this->window){
			SDL_FreeSurface(this->windowSurface);
			SDL_DestroyWindow(this->window);
		}
	}
public:
	/**
	 * 最初や、ニワン語でjumpが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onVideoChanged(const std::string& videoId, const std::string& filepath)
	{
		this->box->loadVideo(this->box, filepath.c_str());
	}
	/**
	 * ニワン語でseekが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onSeek(const std::string& videoId, float vpos)
	{
		std::cerr << "onSeek(" << videoId << "," << vpos << std::endl ;
		std::flush(std::cerr);
	}
public:
	void measure(const int w, const int h, int* const measuredWidth, int* const measuredHeight)
	{
		parent()->measure(w, h, measuredWidth, measuredHeight);
		this->window = SDL_CreateWindow("Saccubus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, *measuredWidth, *measuredHeight, 0);
		if(!this->window) {
			std::cerr << "Failed to create window: " << SDL_GetError() << std::endl << std::flush;
			errorwait(true);
		}
		this->windowSurface = SDL_GetWindowSurface(this->window);
		if(!this->windowSurface) {
			std::cerr << "Failed to get window surface: " << SDL_GetError() << std::endl << std::flush;
			errorwait(true);
		}
	}

	void draw(SaccFrame* const target, SaccFrame* const video)
	{
		SDL_Surface* dst = SDL_CreateRGBSurfaceFrom(target->data,
				target->w, target->h, 32, target->linesize, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000);
		SDL_FillRect(dst, 0, SDL_MapRGB(dst->format, 0, 0, 0));
		SDL_LockSurface(dst);
		{
			std::shared_ptr<saccubus::draw::Context> dctx =
				this->parent()->createContext(saccubus::draw::Renderer::RGB32,
						dst->pixels,
						dst->w,
						dst->h,
						dst->pitch
						);
			std::shared_ptr<saccubus::draw::Sprite> vspr =
				this->parent()->createRawSprite(saccubus::draw::Renderer::RGB32,
				video->data,
				video->w,
				video->h,
				video->linesize
				);
			float time = static_cast<float>(target->vpos);
			this->parent()->draw(dctx, vspr, time);
		}
		SDL_UnlockSurface(dst);

		SDL_BlitSurface(dst,NULL,this->windowSurface,NULL);
		bool running = this->parent()->tasEnabled();
		do{
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_QUIT:
					exit(0);
					return;
				case SDL_MOUSEBUTTONDOWN:
					if(SDL_BUTTON_LEFT == e.button.button){
						this->parent()->click(e.button.x, e.button.y);
						running = false;
					}
					break;
				case SDL_KEYDOWN:
					if(SDLK_SPACE == e.key.keysym.sym){
						running = false;
					}
					break;
				default:
					break;
				}
			}
			SDL_UpdateWindowSurface(this->window);
			if( running ){
				SDL_Delay(16);
			} else if(this->parent()->tasEnabled()) {
				std::cerr << "Processed. "<<target->w<<"x"<<target->h<<". Time:" << target->vpos << std::endl << std::flush;
			}
		} while (running);
		SDL_FreeSurface(dst);
	}
};

class Context{
private:
	DEFINE_MEMBER(private, private, saccubus::Saccubus*, saccubus)
	DEFINE_MEMBER(public, private, FFmpegAdapter*, adapter)
public:
	Context(saccubus::Saccubus* const saccubus, FFmpegAdapter* const adapter)
	{
		this->saccubus(saccubus);
		this->adapter(adapter);
	}
	virtual ~Context()
	{
		delete this->adapter();
		delete this->saccubus();
	}
};

}

//---------------------------------------------------------------------------------------------------------------------

DYNAPI int SaccConfigure(void **sacc, SaccToolBox *box, int argc, char *argv[])
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "failed to init sdl: " << SDL_GetError() << std::endl;
		ffmpeg::errorwait();
		return -5;
	}
	try {
		signal(SIGINT, exit);
		signal(SIGTERM, exit);
		saccubus::Saccubus* const saccubus = new saccubus::Saccubus(std::cout, argc, argv);
		ffmpeg::FFmpegAdapter* const adapter = new ffmpeg::FFmpegAdapter(saccubus, box);
		*sacc = new ffmpeg::Context(saccubus, adapter);

		saccubus->init(adapter);
	} catch (saccubus::logging::Exception & e){
		std::cerr << "Saccubus exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -1;
	} catch (std::exception & e) {
		std::cerr << "Standard exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -2;
	} catch (...) {
		std::cerr << "Unknown error caught" << std::endl << std::flush;
		ffmpeg::errorwait();
		return -3;
	}
	return 0;
}

DYNAPI int SaccMeasure(void *sacc, SaccToolBox *box, int srcWidth, int srcHeight, int* dstWidth, int* dstHeight)
{
	try{
		ffmpeg::Context* const ctx = reinterpret_cast<ffmpeg::Context*>(sacc);
		ctx->adapter()->measure(srcWidth, srcHeight, dstWidth, dstHeight);
	} catch (saccubus::logging::Exception & e){
		std::cerr << "Saccubus exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -1;
	} catch (std::exception & e) {
		std::cerr << "Standard exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -2;
	} catch (...) {
		std::cerr << "Unknown error caught" << std::endl << std::flush;
		ffmpeg::errorwait();
		return -3;
	}
	return 0;
}

DYNAPI int SaccProcess(void *sacc, SaccToolBox *box, SaccFrame *target, SaccFrame* video)
{
	try {
		ffmpeg::Context* const ctx = reinterpret_cast<ffmpeg::Context*>(sacc);
		ctx->adapter()->draw(target, video);
	} catch (saccubus::logging::Exception & e){
		std::cerr << "Saccubus exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -1;
	} catch (std::exception & e) {
		std::cerr << "Standard exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -2;
	} catch (...) {
		std::cerr << "Unknown error caught" << std::endl << std::flush;
		ffmpeg::errorwait();
		return -3;
	}
	return 0;
}

DYNAPI int SaccRelease(void *sacc, SaccToolBox *box)
{
	try {
		ffmpeg::Context* ctx = reinterpret_cast<ffmpeg::Context*>(sacc);

		delete ctx;
	} catch (saccubus::logging::Exception & e){
		std::cerr << "Saccubus exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -1;
	} catch (std::exception & e) {
		std::cerr << "Standard exception caught: " << e.what() << std::endl << std::flush;
		ffmpeg::errorwait();
		return -2;
	} catch (...) {
		std::cerr << "Unknown error caught" << std::endl << std::flush;
		ffmpeg::errorwait();
		return -3;
	}
	SDL_Quit();
	return 0;
}
