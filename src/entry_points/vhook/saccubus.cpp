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
#include <SDL2/SDL.h>
#include "framehook_ext.h"
#include "../../saccubus/Saccubus.h"

class VhookAdapter : public saccubus::Adapter
{
public:
	VhookAdapter()
	{

	}
	virtual ~VhookAdapter()
	{

	}
public:
	/**
	 * 最初や、ニワン語でjumpが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onVideoChanged(const std::string& videoId, const std::string& filepath)
	{
		std::cerr << "onVideoChanged(" << videoId << "," << filepath << std::endl ;
		std::flush(std::cerr);
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
};
#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#endif

struct Context {
	Context():saccubus(0), window(0), adapter(0){
	}
	virtual ~Context(){
		if(adapter){
			delete saccubus;
		}
		if(saccubus){
			delete saccubus;
		}
		if(window){
			SDL_FreeSurface(cairoSurface);
			SDL_FreeSurface(windowSurface);
			SDL_DestroyWindow(window);
		}
	}
	saccubus::Saccubus* saccubus;
	SDL_Window* window;
	SDL_Surface* windowSurface;
	SDL_Surface* cairoSurface;
	VhookAdapter* adapter;
};

//configure用
DLLEXPORT int ExtConfigure(void **ctxp,const toolbox *tbox, int argc, char *argv[])
{
	struct Context* ctx = new Context;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	ctx->saccubus = new saccubus::Saccubus(std::cerr, argc, argv);
	ctx->adapter = new VhookAdapter();
	*ctxp = ctx;
	return 0;
}

//フレーム用
DLLEXPORT void ExtProcess(void *ctx_,const toolbox *tbox,vhext_frame *pict)
{
	struct Context* ctx = reinterpret_cast<struct Context*>(ctx_);
	if(!ctx->window){
		ctx->window = SDL_CreateWindow("Saccubus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pict->w, pict->h, SDL_WINDOW_SHOWN);
		if(!ctx->window) {
			std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
			std::flush(std::cerr);
			exit(0);
		}
		ctx->windowSurface = SDL_GetWindowSurface(ctx->window);
		if(!ctx->windowSurface) {
			std::cerr << "Failed to get window surface: " << SDL_GetError() << std::endl;
			std::flush(std::cerr);
			exit(0);
		}
		ctx->cairoSurface = SDL_CreateRGBSurface(0, pict->w, pict->h, 32,
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
		if(!ctx->windowSurface) {
			std::cerr << "Failed to allocate surface: " << SDL_GetError() << std::endl;
			std::flush(std::cerr);
			exit(0);
		}
		int w,h;
		ctx->saccubus->measure(pict->w, pict->h, &w, &h);
		ctx->saccubus->init(ctx->adapter);
	}
	try {
		SDL_FillRect(ctx->cairoSurface, 0, SDL_MapRGB(ctx->windowSurface->format, 0xff, 0xff, 0xff));
		SDL_LockSurface(ctx->cairoSurface);
		{
			std::tr1::shared_ptr<saccubus::draw::Context> dctx =
				ctx->saccubus->createContext(saccubus::draw::Renderer::ARGB32,
						ctx->cairoSurface->pixels,
						ctx->cairoSurface->w,
						ctx->cairoSurface->h,
						ctx->cairoSurface->pitch
						);
			float time = pict->pts;
			ctx->saccubus->draw(dctx, time, 0);
			std::cerr << "Processed. "<<pict->w<<"x"<<pict->h<<". Time:" << time << std::endl;
			std::flush(std::cerr);
		}
		SDL_UnlockSurface(ctx->cairoSurface);
	} catch (saccubus::logging::Exception& e) {
		std::cerr << "Saccubus Exception caught." << e.what() << std::endl << std::flush;
		exit(-1);
	}
	bool running = true;
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
	SDL_BlitSurface(ctx->cairoSurface, NULL, surf, NULL);
	SDL_BlitSurface(surf,NULL,ctx->windowSurface,NULL);
	while( running ) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				return;
			case SDL_MOUSEBUTTONDOWN:
				if(SDL_BUTTON_LEFT == e.button.button){
					ctx->saccubus->click(e.button.x, e.button.y);
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
		SDL_UpdateWindowSurface(ctx->window);
		if( running ){
			SDL_Delay(16);
		}
	}
	SDL_FreeSurface(surf);
	std::cout << "goto next frame" << std::endl;
}

//終了時に呼ぶ
DLLEXPORT void ExtRelease(void *ctx_,const toolbox *tbox)
{
	struct Context* ctx = reinterpret_cast<struct Context*>(ctx_);
	delete ctx;
	SDL_Quit();
}


