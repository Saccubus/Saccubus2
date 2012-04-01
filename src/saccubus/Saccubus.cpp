/*
 * Saccubus.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <libgen.h>
#include "util/StringUtil.h"
#include "logging/Exception.h"
#include "logging/Logger.h"
#include "Saccubus.h"

namespace saccubus {

static const std::string RESOLVE_PREFIX("--resolve-");
static const std::string TAG("Saccubus");

Saccubus::Saccubus(logging::Logger& log, int argc, char** argv)
:progPath(dirname(const_cast<char*>(argv[0])))
{
	if(argc < 2){
		throw logging::Exception("Called with too few arguments: %d", argc);
	}
	nowVideoId = argv[1];
	log.i(TAG, "Video ID: %s", nowVideoId.c_str());

	for(int i=2;i<argc;++i){
		std::string arg(argv[i]);
		if(i+1<argc && util::startsWith(arg, RESOLVE_PREFIX)){
			++i;
			this->resolveOpts.push_back(std::pair<std::string, std::string>(arg.substr(RESOLVE_PREFIX.size()), argv[i]));
		}
	}
}

Saccubus::~Saccubus() {
	// TODO Auto-generated destructor stub
}

void Saccubus::init(Adapter* const adapter)
{
	this->adapter = adapter;
}

void Saccubus::measure(const int w, const int h, int& measuredWidth, int& measuredHeight)
{
	measuredWidth = w;
	measuredHeight = h;
}

void Saccubus::draw(float vpos, draw::Canvas* canvas, draw::Sprite* videoSprite)
{

}

}
