/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <memory>
#include <cinamo/Logger.h>
#include <map>
#include <string>
#include "classdefs.h"

namespace saccubus {

const std::string PLUGIN_GRAPHIC("gfx");
const std::string PLUGIN_GRAPHIC_CFG_PREFIX(PLUGIN_GRAPHIC+"-");
const std::string PLUGIN_FONT("font");
const std::string PLUGIN_FONT_CFG_PREFIX(PLUGIN_FONT+"-");
const std::string PLUGIN_SHAPE("shape");
const std::string PLUGIN_SHAPE_CFG_PREFIX(PLUGIN_SHAPE+"-");
const std::string PLUGIN_DEPLOY("deploy");
const std::string PLUGIN_DEPLOY_CFG_PREFIX(PLUGIN_DEPLOY+"-");

const std::string PLUGIN_IMPL_CAIRO("cairo");
const std::string PLUGIN_IMPL_ARTISTIC("artistic");
const std::string PLUGIN_IMPL_SIMPLE("simple");

/**
 * プラグインの生成（依存性注入）を行う。
 * スイッチ付きのFactoryメソッドと思えばよろしい。
 */
class PluginOrganizer {
private:
	cinamo::Logger& log;
private:
	std::map<std::string, std::string> config;
private:
	std::map<std::string, std::string> rendererConfig;
	std::map<std::string, std::string> commentFactoryConfig;
	std::map<std::string, std::string> shapeFactoryConfig;
	std::map<std::string, std::string> commentLayerConfig;
public:
	PluginOrganizer(cinamo::Logger& log, const std::map<std::string, std::string>& config);
	virtual ~PluginOrganizer();
public:
	saccubus::draw::Renderer* newRenderer();
	saccubus::draw::CommentFactory* newCommentFactory(draw::Renderer* const renderer);
	saccubus::draw::ShapeFactory* newShapeFactory(draw::Renderer* const renderer);
	saccubus::layer::CommentLayer* newCommentLayer(layer::ThreadLayer* thread, bool isforked);
};

}
