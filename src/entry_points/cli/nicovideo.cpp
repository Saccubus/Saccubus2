//============================================================================
// Name        : nicovideo.cpp
// Author      : PSI
// Version     :
// Copyright   : 2007-2011 psi
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "../../saccubus/Saccubus.h"
#include "../../saccubus/draw/sdl/Canvas.h"
#include "../../saccubus/logging/Exception.h"
using namespace std;
namespace entry_points {
namespace cli {
const unsigned int FACTOR = 3;
const unsigned int FACTORED_INTERVAL = 3*1000/30;

void loop(SDL_Window* window, saccubus::Saccubus& sacc, saccubus::draw::Canvas& canvas) {
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
			default:
				break;
			}
		}

		sacc.draw((float)now/(1000*FACTOR), &canvas, 0);
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
	saccubus::Saccubus sacc(argc, argv);
	int w, h;
	sacc.measure(640, 480, w, h);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		throw saccubus::logging::Exception("Failed to initialize SDL: %s",
				SDL_GetError());
	}
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer) < 0) {
		SDL_Quit();
		throw saccubus::logging::Exception(
				"Failed to create window and renderer: %s", SDL_GetError());
	}

	saccubus::draw::sdl::Canvas canvas(renderer);
	loop(window, sacc, canvas);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
}
}

int main(int argc, char** argv) {
	try {
		return entry_points::cli::main(argc, argv);
	} catch (saccubus::logging::Exception& e) {
		std::cerr << "Saccubus Exception Catched." << e.what() << std::endl;
		return -1;
	} catch (std::exception& e) {
		std::cerr << "Standard Exception Catched." << e.what() << std::endl;
		return -2;
	} catch (...) {
		std::cerr << "Unknwon Exception Catched" << std::endl;
		return -3;
	}
}
