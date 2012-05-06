/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <SDL/SDL.h>
#include "saccubus_adapter.h"
#include "../../saccubus/Saccubus.h"

#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

class FFmpegAdapter : public saccubus::Adapter
{
	DEF_ATTR_ACCESSOR(private, private, saccubus::Saccubus*, parent);
private:
	SaccToolBox* const box;
private:
	SDL_Surface* windowSurface;
	SDL_Surface* cairoSurface;
public:
	FFmpegAdapter(saccubus::Saccubus* const parent, SaccToolBox* const box)
	:box(box)
	,windowSurface(0)
	,cairoSurface(0)
	{
		this->parent(parent);
	}
	virtual ~FFmpegAdapter()
	{
		if(windowSurface){
			SDL_FreeSurface(cairoSurface);
			SDL_FreeSurface(windowSurface);
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
		this->windowSurface = SDL_SetVideoMode(*measuredWidth, *measuredHeight, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
		if(!this->windowSurface) {
			std::cerr << "Failed to get window surface: " << SDL_GetError() << std::endl;
			std::flush(std::cerr);
			exit(0);
		}
		this->cairoSurface = SDL_CreateRGBSurface(0, *measuredWidth, *measuredHeight, 32,
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			0xff000000,
			0x00ff0000,
			0x0000ff00,
			0x000000ff
		#else
			0x00ff0000,
			0x0000ff00,
			0x000000ff,
			0xff000000
		#endif
		);
		if(!this->windowSurface) {
			std::cerr << "Failed to allocate surface: " << SDL_GetError() << std::endl;
			std::flush(std::cerr);
			exit(0);
		}
	}

	void draw(SaccFrame* const pict)
	{
		SDL_FillRect(this->cairoSurface, 0, SDL_MapRGBA(this->windowSurface->format, 0, 0, 0, 0));
		SDL_LockSurface(this->cairoSurface);
		{
			std::tr1::shared_ptr<saccubus::draw::Context> dctx =
				this->parent()->createContext(saccubus::draw::Renderer::ARGB32,
						this->cairoSurface->pixels,
						this->cairoSurface->w,
						this->cairoSurface->h,
						this->cairoSurface->pitch
						);
			float time = static_cast<float>(pict->vpos);
			this->parent()->draw(dctx, time, 0);
			std::cerr << "Processed. "<<pict->w<<"x"<<pict->h<<". Time:" << time << std::endl;
			std::flush(std::cerr);
		}
		SDL_UnlockSurface(this->cairoSurface);

		SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pict->data,
				pict->w,pict->h,24,pict->linesize,
				#if SDL_BYTEORDER == SDL_BIG_ENDIAN
					0xff000000,
					0x00ff0000,
					0x0000ff00,
				#else
					0x000000ff,
					0x0000ff00,
					0x00ff0000,
				#endif
					0x00000000
			);
		SDL_BlitSurface(this->cairoSurface, NULL, surf, NULL);
		SDL_BlitSurface(surf,NULL,this->windowSurface,NULL);
		bool running = true;
		while( running ) {
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
			SDL_Flip(this->windowSurface);
			if( running ){
				SDL_Delay(16);
			}
		}
		SDL_FreeSurface(surf);
		std::cerr << "goto next frame" << std::endl;
	}
};

class Context{
private:
	DEF_ATTR_ACCESSOR(private, private, saccubus::Saccubus*, saccubus)
	DEF_ATTR_ACCESSOR(public, private, FFmpegAdapter*, adapter)
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

//---------------------------------------------------------------------------------------------------------------------

DLLEXPORT int SaccConfigure(void **sacc, SaccToolBox *box, int argc, char *argv[])
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "failed to init sdl: " << SDL_GetError() << std::endl;
		return -5;
	}
	SDL_EnableKeyRepeat(100, 30);
	try {
		saccubus::Saccubus* const saccubus = new saccubus::Saccubus(std::cout, argc, argv);
		FFmpegAdapter* const adapter = new FFmpegAdapter(saccubus, box);
		*sacc = new Context(saccubus, adapter);

		saccubus->init(adapter);
	} catch (saccubus::logging::Exception & e){
		std::cerr << "saccubus exception caught: " << e.what() << std::endl;
		return -1;
	} catch (std::exception & e) {
		std::cerr << "std exception caught: " << e.what() << std::endl;
		return -2;
	} catch (...) {
		std::cerr << "Unknwon error caught" << std::endl;
		return -3;
	}
	return 0;
}

DLLEXPORT int SaccMeasure(void *sacc, SaccToolBox *box, int srcWidth, int srcHeight, int* dstWidth, int* dstHeight)
{
	try{
		Context* const ctx = reinterpret_cast<Context*>(sacc);
		ctx->adapter()->measure(srcWidth, srcHeight, dstWidth, dstHeight);
	} catch (saccubus::logging::Exception & e){
		std::cerr << "saccubus exception caught: " << e.what() << std::endl;
		return -1;
	} catch (std::exception & e) {
		std::cerr << "std exception caught: " << e.what() << std::endl;
		return -2;
	} catch (...) {
		std::cerr << "Unknwon error caught" << std::endl;
		return -3;
	}
	return 0;
}

DLLEXPORT int SaccProcess(void *sacc, SaccToolBox *box, SaccFrame *pict)
{
	try {
		Context* const ctx = reinterpret_cast<Context*>(sacc);
		ctx->adapter()->draw(pict);
	} catch (saccubus::logging::Exception & e){
		std::cerr << "saccubus exception caught: " << e.what() << std::endl;
		return -1;
	} catch (std::exception & e) {
		std::cerr << "std exception caught: " << e.what() << std::endl;
		return -2;
	} catch (...) {
		std::cerr << "Unknwon error caught" << std::endl;
		return -3;
	}
	return 0;
}

DLLEXPORT int SaccRelease(void *sacc, SaccToolBox *box)
{
	try {
		Context* ctx = reinterpret_cast<Context*>(sacc);

		delete ctx;
	} catch (saccubus::logging::Exception & e){
		std::cerr << "saccubus exception caught: " << e.what() << std::endl;
		return -1;
	} catch (std::exception & e) {
		std::cerr << "std exception caught: " << e.what() << std::endl;
		return -2;
	} catch (...) {
		std::cerr << "Unknwon error caught" << std::endl;
		return -3;
	}
	SDL_Quit();
	return 0;
}
