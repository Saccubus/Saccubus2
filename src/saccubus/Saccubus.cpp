/*
 * Saccubus.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <libgen.h>
#include "util/StringUtil.h"
#include "Saccubus.h"

namespace saccubus {

static const std::string RESOLVE_PREFIX("--resolve-");

Saccubus::Saccubus(int argc, char** argv)
:progPath(dirname(const_cast<char*>(argv[0])))
{
	for(int i=1;i<argc;++i){
		std::string arg(argv[i]);
		if(i+1<argc && util::startsWith(arg, RESOLVE_PREFIX)){
			++i;
			this->resolveOpts.insert(std::pair<std::string, std::string>(arg.substr(RESOLVE_PREFIX.size()), argv[i]));
		}
	}

}

Saccubus::~Saccubus() {
	// TODO Auto-generated destructor stub
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
