/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <cinamo/ClassUtil.h>
#include <nicomo/Model.h>
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
	virtual void onVideoChanged(std::string const& videoId, std::string const& filepath) = 0;
	/**
	 * ニワン語でseekが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onSeek(std::string const& videoId, float vpos) = 0;
};

using namespace nicomo::model;

class Saccubus {
	DEFINE_MEMBER(private, private, draw::Renderer*, renderer);
private: /* option */
	bool _tasEnabled;
	std::string ngScript;
public:
	bool tasEnabled() const{ return _tasEnabled; }
private:
	Adapter* adapter;
private:
	std::string programPath;
	std::multimap<std::string, std::string> resolveOpts;
	std::string firstVideoId;
	const Video* currentVideo;
private:
	layer::ThreadLayer* mainThradLayer;
	layer::ThreadLayer* optionalThradLayer;
private:
	PluginOrganizer* pluginOrganizer;
private:
	python::PyBridge* bridge;
	cinamo::Logger* log;
public: //
	Saccubus(std::ostream& logStream, int argc, char** argv);
	virtual ~Saccubus();
public: //公開メソッド
	void init(Adapter* const adapter);
	void measure(const int w, const int h, int* const measuredWidth, int* const measuredHeight);
	void draw(std::shared_ptr<saccubus::draw::Context> ctx, std::shared_ptr<saccubus::draw::Sprite> video, float vpos);
public: /* 外界との接続 */
	std::shared_ptr<saccubus::draw::Context> createContext(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	std::shared_ptr<saccubus::draw::Sprite> createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	void click(int x, int y);
public: // 内部から呼ばれます
	void onVideoChanged(std::string const& videoId);
};

}
