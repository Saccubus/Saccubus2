/*
 * Saccubus.h
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#ifndef SACCUBUS_H_
#define SACCUBUS_H_

#include <string>
#include <map>
#include "draw/Canvas.h"

namespace saccubus {

class Adapter
{
public:
	void onVideoChanged(const std::string& videoId, const std::string& filepath);
	void onSeek(const std::string& videoId, float vpos);
};

class Saccubus {
private:
	const std::string progPath;
	std::map<std::string, std::string> resolveOpts;
public:
	Saccubus(const int argc, const char** argv);
	virtual ~Saccubus();

	void onMeasure(const int w, const int h, int& measuredWidth, int& measuredHeight);
	void onDraw(float vpos, draw::Canvas* canvas);
};

}
#endif /* SACCUBUS_H_ */
