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
#include "../../saccubus/draw/sdl/Renderer.h"
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

void loop() {
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

		sacc.draw((float)now/(1000*FACTOR), 0);

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
	saccubus::Saccubus sacc(std::cout, argc, argv);
	int w, h;
	sacc.measure(640, 480, w, h);

	loop();

	return 0;
}

}}

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
