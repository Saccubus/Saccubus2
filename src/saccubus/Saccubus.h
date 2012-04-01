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
#include <vector>
#include "classdefs.h"

namespace saccubus {

class Adapter
{
public:
	void onVideoChanged(const std::string& videoId, const std::string& filepath);
	void onSeek(const std::string& videoId, float vpos);
	void onFinished();
};

class Saccubus {
private:
	Adapter* adapter;
private:
	const std::string progPath;
	std::vector<std::pair<std::string, std::string> > resolveOpts;
	std::string nowVideoId;
private:
	python::PyBridge* const bridge;
public:
	Saccubus(logging::Logger& log, int argc, char** argv);
	virtual ~Saccubus();

	void init(Adapter* const adapter);
	void measure(const int w, const int h, int& measuredWidth, int& measuredHeight);
	void draw(float vpos, draw::Canvas* canvas, draw::Sprite* videoSprite);
	void onVideoChanged(const std::string& videoId);
};

}
#endif /* SACCUBUS_H_ */
