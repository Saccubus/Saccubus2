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
#include <iostream>
#include "classdefs.h"

namespace saccubus {

static const std::string PROGRAM_NAME("Saccubus");
static const std::string PROGRAM_VERSION("1.00");

class Adapter
{
public:
	Adapter(){}
	virtual ~Adapter(){}
public:
	/**
	 * 最初や、ニワン語でjumpが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onVideoChanged(const std::string& videoId, const std::string& filepath) = 0;
	/**
	 * ニワン語でseekが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onSeek(const std::string& videoId, float vpos) = 0;
};

class Saccubus {
private:
	Adapter* adapter;
private:
	const std::string progPath;
	std::vector<std::pair<std::string, std::string> > resolveOpts;
	std::string firstVideoId;
	const meta::Video* currentVideo;
private:
	python::PyBridge* bridge;
	logging::Logger* log;
public: //
	Saccubus(std::ostream& logStream, int argc, char** argv);
	virtual ~Saccubus();
public: //公開メソッド
	void init(Adapter* const adapter);
	void measure(const int w, const int h, int& measuredWidth, int& measuredHeight);
	void draw(float vpos, draw::Canvas* canvas, draw::Sprite* videoSprite);
public: // 内部から呼ばれます
	void onVideoChanged(const std::string& videoId);
};

}
#endif /* SACCUBUS_H_ */
