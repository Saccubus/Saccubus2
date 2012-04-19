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
#include <SDL2/SDL_video.h>
#include "../../saccubus/Saccubus.h"
#include "../../saccubus/draw/Renderer.h"
#include "../../saccubus/logging/Exception.h"
#include "../../saccubus/logging/Logger.h"
using namespace std;
namespace entry_points {
namespace cli {
const unsigned int FACTOR = 3;
const unsigned int FACTORED_INTERVAL = 3*1000/30;

class CLIAdapter : public saccubus::Adapter
{
public:
	CLIAdapter()
	{

	}
	virtual ~CLIAdapter()
	{

	}
public:
	/**
	 * 最初や、ニワン語でjumpが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onVideoChanged(const std::string& videoId, const std::string& filepath)
	{
	}
	/**
	 * ニワン語でseekが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onSeek(const std::string& videoId, float vpos)
	{

	}
};

void loop(int w, int h, SDL_Window* const window, SDL_Surface* const windowSurface, saccubus::Saccubus* const saccubus) {

	unsigned long long now = SDL_GetTicks();
	unsigned long long nextFactored = now*FACTOR+FACTORED_INTERVAL;
	unsigned long long fpsTime = now;
	unsigned int fps = 0;
	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				return;
			case SDL_MOUSEMOTION:
			default:
				break;
			}
		}

		SDL_FillRect(windowSurface, 0, SDL_MapRGB(windowSurface->format, 0xff, 0xff, 0xff));
		SDL_LockSurface(windowSurface);
		{
			std::tr1::shared_ptr<saccubus::draw::Context> ctx =
					saccubus->createContext(saccubus::draw::Renderer::RGBA32, windowSurface->pixels, windowSurface->w, windowSurface->h, windowSurface->pitch);
			saccubus->draw(ctx, (float)now/(1000*FACTOR), 0);
		}
		SDL_UnlockSurface(windowSurface);

		SDL_UpdateWindowSurface(window);

		++fps;
		now = SDL_GetTicks();
		if (now - fpsTime >= 1000) {
			printf("FPS:%d\n", fps);
			fpsTime += 1000;
			fps = 0;
		}

		uint32_t nowFactored = now * FACTOR;
		if (nowFactored < nextFactored) {
			SDL_Delay((nextFactored - nowFactored) / FACTOR);
		}
		nextFactored += FACTORED_INTERVAL;
	}
}

int main(int argc, char** argv) {
	int w, h;
	saccubus::Saccubus sacc(std::cout, argc, argv);
	sacc.measure(640, 480, &w, &h);

	SDL_Window* const window = SDL_CreateWindow("Saccubus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if(!window) throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to create SDL window: %s", SDL_GetError());
	SDL_Surface* const windowSurface = SDL_GetWindowSurface(window);
	if(!windowSurface) throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to get SDL window surface: %s", SDL_GetError());

	CLIAdapter adapter;
	sacc.init(&adapter);

	loop(w, h, window, windowSurface, &sacc);

	SDL_FreeSurface(windowSurface);
	SDL_DestroyWindow(window);

	return 0;
}

}}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	try {
		int result = entry_points::cli::main(argc, argv);
		SDL_Quit();
		return result;
	} catch (saccubus::logging::Exception& e) {
		std::cerr << "Saccubus Exception caught." << e.what() << std::endl;
		std::cerr.flush();
		SDL_Quit();
		return -1;
	} catch (std::exception& e) {
		std::cerr << "Standard Exception caught." << e.what() << std::endl;
		std::cerr.flush();
		SDL_Quit();
		return -2;
	} catch (...) {
		std::cerr << "Unknwon Exception caught." << std::endl;
		std::cerr.flush();
		SDL_Quit();
		return -3;
	}
}
