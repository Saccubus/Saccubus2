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

#ifndef SACCUBUS_H_
#define SACCUBUS_H_

#include <string>
#include <map>
#include <iostream>
#include <tr1/memory>
#include "util/ClassAccessor.h"
#include "classdefs.h"
#include "draw/Renderer.h"

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
	DEF_ATTR_ACCESSOR(private, private, draw::Renderer*, renderer);
private:
	Adapter* adapter;
private:
	std::string programPath;
	std::multimap<std::string, std::string> resolveOpts;
	std::string firstVideoId;
	const meta::Video* currentVideo;
private:
	layer::ThreadLayer* mainThradLayer;
	layer::ThreadLayer* optionalThradLayer;
private:
	PluginOrganizer* pluginOrganizer;
private:
	python::PyBridge* bridge;
	logging::Logger* log;
public: //
	Saccubus(std::ostream& logStream, int argc, char** argv);
	virtual ~Saccubus();
public: //公開メソッド
	void init(Adapter* const adapter);
	void measure(const int w, const int h, int* const measuredWidth, int* const measuredHeight);
	void draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos, draw::Sprite* videoSprite);
public: /* 外界との接続 */
	std::tr1::shared_ptr<saccubus::draw::Context> createContext(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	draw::RawSprite* createRawSprite(int w, int h);
	void click(int x, int y);
public: // 内部から呼ばれます
	void onVideoChanged(const std::string& videoId);
};

}
#endif /* SACCUBUS_H_ */
