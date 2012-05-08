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

#include <getopt.h>
#include <cstdlib>
#include <iomanip>
#include <libgen.h>
#include <string.h>
#include "python/PyBridge.h"
#include "util/StringUtil.h"
#include "logging/Exception.h"
#include "logging/Logger.h"
#include "meta/MetaInfo.h"
#include "meta/PlayInfo.h"
#include "meta/Video.h"
#include "PluginOrganizer.h"
#include "Saccubus.h"
#include "draw/Renderer.h"
#include "draw/Context.h"
#include "layer/ThreadLayer.h"
#include "util/OptionParser.h"
#include "SaccubusOptions.h"

namespace saccubus {

static const std::string TAG("Saccubus");

void usage(std::ostream* logStream, int argc, char** argv){
	static const std::string USAGE_TAB="    ";
	*logStream << "Usage: " << basename(argv[0]) << " [switches] [--] [programfile]" << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--trace" << "set log level." << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--verbose" << "set log level." << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--debug"<<"set log level." << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--warning"<<"set log level." << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--error"<<"set log level." << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--version"<<"output the version, then exit." << std::endl;
	*logStream << USAGE_TAB << std::left << std::setw(15) << "--help"<<"output the help, then exit." << std::endl;
	exit(0);
}

void version(std::ostream* logStream, int argc, char** argv){
	*logStream << PROGRAM_NAME << " "<< PROGRAM_VERSION <<" ( build at " << __DATE__ << " " << __TIME__ << " )" << std::endl;
	exit(0);
}

Saccubus::Saccubus(std::ostream& logStream, int argc, char** argv)
:_tasEnabled(false)
,ngScript("")
,currentVideo(0)
,mainThradLayer(0)
,optionalThradLayer(0)
,bridge(0)
{
	{
		char* argv0 = new char[strlen(argv[0])+1];
		strcpy(argv0, argv[0]);
		this->programPath = dirname(argv0);
		delete [] argv0;
	}
	logging::Logger::Level level = logging::Logger::WARN_;
	std::map<std::string, std::string> organizerArg;
	std::vector<std::string> left;

	{ /* オプションのパース */
		util::OptionParser parser;
		parser.add(new FlagOption<logging::Logger::Level>("trace", level, logging::Logger::TRACE_));
		parser.add(new FlagOption<logging::Logger::Level>("verbose", level, logging::Logger::VERBOSE_));
		parser.add(new FlagOption<logging::Logger::Level>("debug", level, logging::Logger::DEBUG_));
		parser.add(new FlagOption<logging::Logger::Level>("info", level, logging::Logger::INFO_));
		parser.add(new FlagOption<logging::Logger::Level>("warning", level, logging::Logger::WARN_));
		parser.add(new FlagOption<logging::Logger::Level>("error", level, logging::Logger::ERROR_));
		parser.add(new FunctionOption("version", std::tr1::bind(&version, &logStream, argc, argv)));
		parser.add(new FunctionOption("help", std::tr1::bind(&usage, &logStream, argc, argv)));
		parser.add(new FlagOption<bool>("enable-tas", this->_tasEnabled, true));
		parser.add(new ValueOption<std::string>("ng-script", this->ngScript));
		parser.add(new PreifxOption<std::multimap<std::string, std::string> >("resolve-", this->resolveOpts));
		parser.add(new PreifxOption<std::map<std::string, std::string> >("plugin-", organizerArg));

		parser.parse(argc, argv, left);
	}

	this->log = new logging::Logger(logStream, level);
	this->bridge = new python::PyBridge(*this->log);
	this->pluginOrganizer = new PluginOrganizer(*this->log, organizerArg);

	this->renderer(this->pluginOrganizer->newRenderer());

	if(optind >= argc){
		throw logging::Exception(__FILE__, __LINE__, "You need to set video id!");
	}else{
		firstVideoId = argv[optind];
		log->i(TAG, "First Video ID: %s", firstVideoId.c_str());
	}

}

Saccubus::~Saccubus() {
	if(currentVideo){
		delete currentVideo;
	}
	delete this->renderer();
	this->renderer(0);
	delete pluginOrganizer;
	delete bridge;
	delete log;
}

void Saccubus::init(Adapter* const adapter)
{
	this->adapter = adapter;

	//最初は自分でイベントを起こす（それ以降はNekomataで起こす）
	this->onVideoChanged(firstVideoId);
}

void Saccubus::measure(const int w, const int h, int* const measuredWidth, int* const measuredHeight)
{
	if(this->mainThradLayer){
		this->mainThradLayer->measure(w, h, measuredWidth, measuredHeight);
	}
	if(this->optionalThradLayer){
		this->optionalThradLayer->measure(*measuredWidth, *measuredHeight, measuredWidth, measuredHeight);
	}
}

void Saccubus::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, std::tr1::shared_ptr<saccubus::draw::Sprite> video, float vpos)
{
	if(video.get()){
		video->draw(ctx, static_cast<int>((ctx->width()-video->width())/2), static_cast<int>((ctx->height()-video->height())/2));
	}
	if(this->mainThradLayer){
		this->mainThradLayer->draw(ctx, vpos);
	}
	if(this->optionalThradLayer){
		this->optionalThradLayer->draw(ctx, vpos);
	}
}

void Saccubus::click(int x, int y)
{
	if(this->mainThradLayer){
		this->mainThradLayer->onClick(x,y);
	}
	if(this->optionalThradLayer){
		this->optionalThradLayer->onClick(x,y);
	}
}

std::tr1::shared_ptr<saccubus::draw::Context> Saccubus::createContext(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
{
	return this->renderer()->createContext(fmt, data, w, h, stride);
}
std::tr1::shared_ptr<saccubus::draw::Sprite> Saccubus::createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
{
	return std::tr1::shared_ptr<saccubus::draw::Sprite>(this->renderer()->createRawSprite(fmt, data, w, h, stride));
}

void Saccubus::onVideoChanged(const std::string& videoId)
{
	{ /* 現在のスレッドの削除 */
		if(this->currentVideo){
			this->log->i(TAG, "Context deleted: %s", this->currentVideo->metaInfo()->title().c_str());
			delete this->currentVideo;
			this->currentVideo = 0;
		}
		if(this->mainThradLayer){
			delete this->mainThradLayer;
			this->mainThradLayer = 0;
		}
		if(this->optionalThradLayer){
			delete this->optionalThradLayer;
			this->optionalThradLayer = 0;
		}
	}

	{ /* 新しいビデオの、XMLファイルやメタ情報・プレイ情報のパース */
		std::vector<std::pair<std::string, std::string> > arg(this->resolveOpts.begin(), this->resolveOpts.end());
		arg.push_back(std::pair<std::string, std::string>("video-id", videoId));
		const meta::Video* video = bridge->resolveResource(videoId, arg);
		this->currentVideo = video;
		this->log->i(TAG, "Context entered: %s", this->currentVideo->metaInfo()->title().c_str());
	}

	{ /* スレッドレイヤの作成 */
		this->mainThradLayer = new layer::ThreadLayer(
				*log,
				*(this->currentVideo->thread(this->currentVideo->playInfo()->thread())),
				this->ngScript,
				this->bridge,
				this->currentVideo->playInfo()->replaceTable(),
				this->renderer(),
				this->pluginOrganizer
				);
		if(this->currentVideo->playInfo()->optional_thread() >= 0){
			this->optionalThradLayer = new layer::ThreadLayer(
					*log,
					*(this->currentVideo->thread(this->currentVideo->playInfo()->optional_thread())),
					this->ngScript,
					this->bridge,
					this->currentVideo->playInfo()->replaceTable(),
					this->renderer(),
					this->pluginOrganizer
					);
		}
	}

	if(adapter)
	{
		adapter->onVideoChanged(videoId, this->currentVideo->videofile());
	}
}

}
