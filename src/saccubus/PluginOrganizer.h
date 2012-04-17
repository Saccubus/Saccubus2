/*
 * PluginOrganizer.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef PLUGINORGANIZER_H_
#define PLUGINORGANIZER_H_

#include <tr1/memory>
#include <map>
#include <string>
#include "classdefs.h"

namespace saccubus {

const std::string PLUGIN_GRAPHIC("gfx");
const std::string PLUGIN_GRAPHIC_CFG_PREFIX(PLUGIN_GRAPHIC+"-");
const std::string PLUGIN_TEXT("text");
const std::string PLUGIN_TEXT_CFG_PREFIX(PLUGIN_TEXT+"-");
const std::string PLUGIN_COMMENT("comment");
const std::string PLUGIN_COMMENT_CFG_PREFIX(PLUGIN_COMMENT+"-");

const std::string PLUGIN_IMPL_SDL("sdl");
const std::string PLUGIN_IMPL_SIMPLE("simple");

/**
 * プラグインの生成（依存性注入）を行う。
 * スイッチ付きのFactoryメソッドと思えばよろしい。
 */
class PluginOrganizer {
private:
	logging::Logger& log;
private:
	std::map<std::string, std::string> config;
private:
	std::map<std::string, std::string> rendererConfig;
	std::map<std::string, std::string> commentFactoryConfig;
	std::map<std::string, std::string> commentLayerConfig;
public:
	PluginOrganizer(logging::Logger& log, const std::map<std::string, std::string>& config);
	virtual ~PluginOrganizer();
public:
	saccubus::draw::Renderer* newRenderer(const int w, const int h);
	saccubus::draw::CommentFactory* newCommentFactory(draw::Renderer* const renderer);
	saccubus::layer::CommentLayer* newCommentLayer();
};

}
#endif /* PLUGINORGANIZER_H_ */
