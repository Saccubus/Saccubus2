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
// FIXME: ちょーバッドノウハウ
// http://www3.kct.ne.jp/~mt03605z/fswiki/index.cgi?page=Plamo+%CC%EE%CE%C9%A5%D3%A5%EB%A5%C9
// http://code.google.com/p/ffmpegsource/issues/detail?id=11
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
//http://ffmpeg-users.933282.n4.nabble.com/undefined-reference-to-all-libavcodec-libavformat-functions-td942778.html
extern "C" {
#include <ffmpeg/libavutil/avutil.h>
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libswscale/swscale.h>
}
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
private:
	saccubus::Saccubus & parent;
public:
	CLIAdapter(saccubus::Saccubus & parent)
	:parent(parent)
	,formatContext(0)
	,videoStreamIndex(-1)
	,audioStreamIndex(-1)
	,rawFrame(0)
	,rgbFrame(0)
	,swsContext(0)
	,buffer(0)
	,srcWidth(-1)
	,srcHeight(-1)
	,dstWidth(-1)
	,dstHeight(-1)
	,window(0)
	,windowSurface(0)
	{
		av_register_all();
	}
	virtual ~CLIAdapter()
	{
		if(this->windowSurface){
			SDL_FreeSurface(this->windowSurface);
		}
		if(this->window){
			SDL_DestroyWindow(this->window);
		}
		closeCodec();
	}
private:
	AVFormatContext *formatContext;
	int videoStreamIndex;
	int audioStreamIndex;
	AVFrame* rawFrame;
	AVFrame* rgbFrame;
	struct SwsContext *swsContext;
	uint8_t* buffer;
	int srcWidth, srcHeight;
	int dstWidth, dstHeight;
private:
	SDL_Window* window;
	SDL_Surface* windowSurface;
private:
	bool closeCodec(){
		bool firstLaunch = true;
		if(this->buffer){
			av_free(this->buffer);
			firstLaunch &= false;
		}
		this->buffer = 0;
		if(this->rgbFrame){
			av_free(this->rgbFrame);
			firstLaunch &= false;
		}
		this->rgbFrame = 0;
		if(this->rawFrame){
			av_free(this->rawFrame);
			firstLaunch &= false;
		}
		this->rawFrame = 0;
		if(this->swsContext){
			sws_freeContext(this->swsContext);
			firstLaunch &= false;
		}
		this->swsContext = 0;
		if(videoStreamIndex >= 0){
			avcodec_close(this->formatContext->streams[videoStreamIndex]->codec);
			firstLaunch &= false;
		}
		videoStreamIndex=-1;
		if(audioStreamIndex >= 0){
			avcodec_close(this->formatContext->streams[audioStreamIndex]->codec);
			firstLaunch &= false;
		}
		audioStreamIndex=-1;
		if(this->formatContext)
		{
			av_close_input_file(this->formatContext);
			firstLaunch &= false;
		}
		this->formatContext=0;
		return firstLaunch;
	}
	void initSDL(int width, int height){
		this->window = SDL_CreateWindow("Saccubus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if(!this->window) throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to create SDL window: %s", SDL_GetError());
		this->windowSurface = SDL_GetWindowSurface(window);
		if(!this->windowSurface) throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to get SDL window surface: %s", SDL_GetError());
	}
public:
	/**
	 * 最初や、ニワン語でjumpが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onVideoChanged(const std::string& videoId, const std::string& filepath)
	{
		const bool isFirst = closeCodec();
		const char* filename = filepath.c_str();
		if(avformat_open_input(&formatContext, filename, 0, 0) != 0){
			throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to read file: %s", filepath.c_str());
		}
		if(av_find_stream_info(formatContext)<0){
			throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to read stream info: %s", filepath.c_str());
		}
		this->videoStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
		this->audioStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, audioStreamIndex, 0, 0);

		AVCodec* const videoCodec = videoStreamIndex >= 0 ? avcodec_find_decoder(this->formatContext->streams[videoStreamIndex]->codec->codec_id) : 0;
		AVCodec* const audioCodec = audioStreamIndex >= 0 ? avcodec_find_decoder(this->formatContext->streams[audioStreamIndex]->codec->codec_id) : 0;

		if(avcodec_open(this->formatContext->streams[this->videoStreamIndex]->codec, videoCodec) < 0){
			throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to open codec: %s", filepath.c_str());
		}
		if(avcodec_open(this->formatContext->streams[this->audioStreamIndex]->codec, audioCodec) < 0){
			throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to open codec: %s", filepath.c_str());
		}

		this->srcWidth = this->formatContext->streams[videoStreamIndex]->codec->width;
		this->srcHeight = this->formatContext->streams[videoStreamIndex]->codec->height;

		if(isFirst){
			parent.measure(this->srcWidth, this->srcHeight, &this->dstWidth, &this->dstHeight);
			initSDL(this->dstWidth, this->dstHeight);
		}

		this->rawFrame = avcodec_alloc_frame();
		this->rgbFrame = avcodec_alloc_frame();
		this->swsContext = sws_getContext(this->srcWidth, this->srcHeight, this->formatContext->streams[this->videoStreamIndex]->codec->pix_fmt, this->dstWidth, this->dstHeight, PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);
		this->buffer = reinterpret_cast<uint8_t*>(av_malloc(avpicture_get_size(PIX_FMT_RGB24, srcWidth, srcHeight)*sizeof(uint8_t)));
		avpicture_fill(reinterpret_cast<AVPicture*>(this->rgbFrame), this->buffer, PIX_FMT_RGB24, srcWidth, srcHeight);
	}
private:
	void runFrame(float* vpos,void** data, int* stride){
		AVPacket packet;
		while(av_read_frame(this->formatContext, &packet) >= 0){
			if(packet.stream_index == this->videoStreamIndex){
				int gotPicture = 0;
				if(avcodec_decode_video2(this->formatContext->streams[videoStreamIndex]->codec, this->rawFrame, &gotPicture, &packet) < 0){
					throw saccubus::logging::Exception(__FILE__, __LINE__, "failed to decode video.");
				}
				if(gotPicture){
					sws_scale(this->swsContext, this->rawFrame->data, this->rawFrame->linesize, 0, this->srcHeight, this->rgbFrame->data, this->rgbFrame->linesize);
					double pts = (packet.dts != static_cast<int64_t>(AV_NOPTS_VALUE)) ? packet.dts : 0;
					pts *= av_q2d(this->formatContext->streams[videoStreamIndex]->time_base);
					*vpos = static_cast<float>(pts);
					*data = this->rgbFrame->data[this->rgbFrame->display_picture_number];
					*stride = this->rgbFrame->linesize[this->rgbFrame->display_picture_number];
					return;
				}
			}else if(packet.stream_index == this->audioStreamIndex){
				std::cout << "audio packet caught" << std::endl;
			}
		}
	}
public:
	void loop(){
		unsigned long long now = 0;//SDL_GetTicks();
		unsigned long long nextFactored = now*FACTOR+FACTORED_INTERVAL;
		unsigned long long fpsTime = now;
		unsigned int fps = 0;
		while (1) {
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_QUIT:
					return;
				case SDL_MOUSEBUTTONDOWN:
					if(SDL_BUTTON_LEFT == e.button.button){
						parent.click(e.button.x, e.button.y);
					}
					break;
				default:
					break;
				}
			}

			float vpos;
			void* data;
			int stride;
			runFrame(&vpos, &data, &stride);
			SDL_Surface* pict = SDL_CreateRGBSurfaceFrom(data, this->dstWidth, this->dstHeight, 24, stride, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000);
			SDL_BlitSurface(pict, 0, windowSurface, 0);
			SDL_FreeSurface(pict);
			SDL_LockSurface(windowSurface);
			{
				std::tr1::shared_ptr<saccubus::draw::Context> ctx =
						parent.createContext(saccubus::draw::Renderer::ARGB32, windowSurface->pixels, windowSurface->w, windowSurface->h, windowSurface->pitch);
				parent.draw(ctx, vpos, 0);
			}
			SDL_UnlockSurface(windowSurface);

			SDL_UpdateWindowSurface(window);

			++fps;
			/*
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
			*/
			SDL_Delay(16);
			now = vpos;
		}
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


}

int main(int argc, char** argv) {
	saccubus::Saccubus sacc(std::cout, argc, argv);
	CLIAdapter adapter(sacc);
	sacc.init(&adapter);

	adapter.loop();

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
