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

#include "PluginOrganizer.h"
#include "logging/Exception.h"
#include "logging/Logger.h"
#include "util/StringUtil.h"
#include "draw/cairo/SimpleCommentFactory.h"
#include "draw/cairo/ArtisticCommentFactory.h"
#include "draw/cairo/SimpleShapeFactory.h"
#include "draw/cairo/Renderer.h"
#include "layer/SimpleCommentLayer.h"
#include "layer/ArtisticCommentLayer.h"

namespace saccubus {

const std::string TAG("PluginOrganizer");

PluginOrganizer::PluginOrganizer(logging::Logger& log, const std::map<std::string, std::string>& config)
:log(log), config(config.begin(), config.end()){
	//デフォルトの値を設定
	// insertは、すでに値がある場合は上書きされない。
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_GRAPHIC, PLUGIN_IMPL_CAIRO));
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_FONT, PLUGIN_IMPL_SIMPLE));
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_SHAPE, PLUGIN_IMPL_SIMPLE));
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_DEPLOY, PLUGIN_IMPL_SIMPLE));
	for(std::map<std::string, std::string>::const_iterator it = config.begin(); it != config.end(); ++it){
		if(util::startsWith(it->first, PLUGIN_GRAPHIC_CFG_PREFIX)){
			this->rendererConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_GRAPHIC_CFG_PREFIX.length()),
							it->second
					));
		}else if(util::startsWith(it->first, PLUGIN_FONT_CFG_PREFIX)){
			this->commentFactoryConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_FONT_CFG_PREFIX.length()),
							it->second
					));
		}else if(util::startsWith(it->first, PLUGIN_DEPLOY_CFG_PREFIX)){
			this->commentLayerConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_DEPLOY_CFG_PREFIX.length()),
							it->second
					));
		}else if(util::startsWith(it->first, PLUGIN_SHAPE_CFG_PREFIX)){
			this->shapeFactoryConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_SHAPE_CFG_PREFIX.length()),
							it->second
					));
		}else{
			log.w(TAG, "Unknwon config: (%s) = (%s)", it->first.c_str(), it->second.c_str());
		}
	}

}

PluginOrganizer::~PluginOrganizer() {
}

saccubus::draw::CommentFactory* PluginOrganizer::newCommentFactory(draw::Renderer* const renderer)
{
	if(PLUGIN_IMPL_CAIRO == config[PLUGIN_GRAPHIC] && PLUGIN_IMPL_SIMPLE == config[PLUGIN_FONT]){
		draw::cairo::Renderer* _renderer = dynamic_cast<draw::cairo::Renderer*>(renderer);
		if(!_renderer){
			throw logging::Exception(__FILE__, __LINE__,
					"[BUG] Comment factory corresponding to [graphic: %s, text: %s] needs draw::cairo::Renderer*, but got %s",
					config[PLUGIN_GRAPHIC].c_str(),
					config[PLUGIN_DEPLOY].c_str(),
					typeid(renderer).name()
					);
		}
		return new saccubus::draw::cairo::SimpleCommentFactory(log, _renderer, this->commentFactoryConfig);
	}else if(PLUGIN_IMPL_CAIRO == config[PLUGIN_GRAPHIC] && PLUGIN_IMPL_ARTISTIC == config[PLUGIN_FONT]){
		draw::cairo::Renderer* _renderer = dynamic_cast<draw::cairo::Renderer*>(renderer);
		if(!_renderer){
			throw logging::Exception(__FILE__, __LINE__,
					"[BUG] Comment factory corresponding to [graphic: %s, text: %s] needs draw::cairo::Renderer*, but got %s",
					config[PLUGIN_GRAPHIC].c_str(),
					config[PLUGIN_DEPLOY].c_str(),
					typeid(renderer).name()
					);
		}
		return new saccubus::draw::cairo::ArtisticCommentFactory(log, _renderer, this->commentFactoryConfig);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment factory plugin corresponding to [graphic: %s, text: %s]",
			config[PLUGIN_GRAPHIC].c_str(),
			config[PLUGIN_DEPLOY].c_str()
			);
}
saccubus::draw::ShapeFactory* PluginOrganizer::newShapeFactory(draw::Renderer* const renderer)
{
	if(PLUGIN_IMPL_CAIRO == config[PLUGIN_GRAPHIC] && PLUGIN_IMPL_SIMPLE == config[PLUGIN_SHAPE]){
		draw::cairo::Renderer* _renderer = dynamic_cast<draw::cairo::Renderer*>(renderer);
		if(!_renderer){
			throw logging::Exception(__FILE__, __LINE__,
					"[BUG] Shape factory corresponding to [graphic: %s, shape: %s] needs draw::cairo::Renderer*, but got %s",
					config[PLUGIN_GRAPHIC].c_str(),
					config[PLUGIN_SHAPE].c_str(),
					typeid(renderer).name()
					);
		}
		return new saccubus::draw::cairo::SimpleShapeFactory(log, _renderer, this->shapeFactoryConfig);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment shape plugin corresponding to [graphic: %s, shape: %s]",
			config[PLUGIN_GRAPHIC].c_str(),
			config[PLUGIN_SHAPE].c_str()
			);
}
saccubus::draw::Renderer* PluginOrganizer::newRenderer()
{
	if(PLUGIN_IMPL_CAIRO == config[PLUGIN_GRAPHIC]){
		return new saccubus::draw::cairo::Renderer(log, this->rendererConfig);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no renderer plugin corresponding to [graphic: %s]",
			config[PLUGIN_GRAPHIC].c_str()
			);
}
saccubus::layer::CommentLayer* PluginOrganizer::newCommentLayer(layer::ThreadLayer* thread, bool isforked)
{
	if(PLUGIN_IMPL_SIMPLE == config[PLUGIN_DEPLOY]){
		return new layer::SimpleCommentLayer(log, this->commentLayerConfig, thread, isforked);
	}else if(PLUGIN_IMPL_ARTISTIC == config[PLUGIN_DEPLOY]){
		return new layer::ArtisticCommentLayer(log, this->commentLayerConfig, thread, isforked);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment layer plugin corresponding to [comment: %s]",
			config[PLUGIN_DEPLOY].c_str()
			);
}

}
