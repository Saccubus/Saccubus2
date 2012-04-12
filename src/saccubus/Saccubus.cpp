/*
 * Saccubus.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <getopt.h>
#include <cstdlib>
#include <libgen.h>
#include "python/PyBridge.h"
#include "util/StringUtil.h"
#include "logging/Exception.h"
#include "logging/Logger.h"
#include "meta/MetaInfo.h"
#include "meta/Video.h"
#include "Saccubus.h"

namespace saccubus {

static const std::string RESOLVE_PREFIX("--resolve-");
static const std::string TAG("Saccubus");

const struct option ARG_OPTIONS[] = {
		{"trace", no_argument, 0, 1},
		{"verbose", no_argument, 0, 2},
		{"debug", no_argument, 0, 3},
		{"info", no_argument, 0, 4},
		{"warning", no_argument, 0, 5},
		{"error", no_argument, 0, 6},
		{"help", no_argument, 0, 7},
		{"version", no_argument, 0, 8},
		{0,0,0,0}
};

void usage(std::ostream& logStream, int argc, char* argv[]){
	static const std::string USAGE_TAB="    ";
/*
	cout << "Usage: " << basename(argv[0]) << " [switches] [--] [programfile]" << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--trace" << "set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--verbose" << "set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--debug"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--warning"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--error"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--dump"<<"output dump of AST, then exit." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--version"<<"output the version, then exit." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "-h, --help"<<"output the help, then exit." << endl;
*/
	exit(0);
}

void version(std::ostream& logStream, int argc, char* argv[]){
/*
		cout << nekomata::PROGRAM_NAME << ": "<< nekomata::PROGRAM_VERSION <<" (build at " << __DATE__ << " " << __TIME__ << " )" << endl;
*/
	exit(0);
}

Saccubus::Saccubus(std::ostream& logStream, int argc, char** argv)
:progPath(dirname(const_cast<char*>(argv[0])))
,bridge(0)
{
	logging::Logger::Level level = logging::Logger::WARN_;
	int index = 0;
	while ( 1 )
	{
		/*
		 * CLI、ffmpegの双方で同じオプションを使えるようにするために、
		 * ここでオプションをパースする。
		 */
		int opt = getopt_long(argc, argv, "h", ARG_OPTIONS, &index);
		if ( opt < 0 )
		{
			break;
		}
		switch (opt)
		{
		case 1:
			level = logging::Logger::TRACE_;
			break;
		case 2:
			level = logging::Logger::VERBOSE_;
			break;
		case 3:
			level = logging::Logger::DEBUG_;
			break;
		case 4:
			level = logging::Logger::INFO_;
			break;
		case 5:
			level = logging::Logger::WARN_;
			break;
		case 6:
			level = logging::Logger::ERROR_;
			break;
		case 7:
		case 'h':
			usage(logStream, argc, argv);
			break;
		case 8:
			version(logStream, argc, argv);
			break;
		case '?':
			exit(-1);
			break;
		default:
		{
			std::string arg(argv[index]);
			if(index+1<argc && util::startsWith(arg, RESOLVE_PREFIX)){
				++index;
				this->resolveOpts.push_back(std::pair<std::string, std::string>(arg.substr(RESOLVE_PREFIX.size()), argv[index]));
			}
			break;
		}
		}
	}

	this->log = new logging::Logger(logStream, level);
	this->bridge = new python::PyBridge(*this->log);

	if(optind >= argc){
		throw logging::Exception("You need to set video id!");
	}else{
		firstVideoId = argv[optind];
		log->i(TAG, "First Video ID: %s", firstVideoId.c_str());
	}

}

Saccubus::~Saccubus() {
	if(currentVideo){
		delete currentVideo;
	}
	delete bridge;
	delete log;
}

void Saccubus::init(Adapter* const adapter)
{
	this->adapter = adapter;

	//最初は自分でイベントを起こす（それ以降はNekomataで起こす）
	this->onVideoChanged(firstVideoId);
}

void Saccubus::measure(const int w, const int h, int& measuredWidth, int& measuredHeight)
{
	measuredWidth = w;
	measuredHeight = h;
}

void Saccubus::draw(float vpos, draw::Canvas* canvas, draw::Sprite* videoSprite)
{

}

void Saccubus::onVideoChanged(const std::string& videoId)
{
	std::vector<std::pair<std::string, std::string> > arg(this->resolveOpts.begin(), this->resolveOpts.end());
	arg.push_back(std::pair<std::string, std::string>("video-id", videoId));
	const meta::Video* video = bridge->resolveResource(videoId, arg);
	if(this->currentVideo){
		this->log->i("Context deleted: %s", this->currentVideo->metaInfo()->title());
		delete this->currentVideo;
	}
	this->currentVideo = video;
	this->log->i("Context entered: %s", this->currentVideo->metaInfo()->title());
	if(adapter)
	{
		adapter->onVideoChanged(videoId, video->videofile());
	}
}

}
