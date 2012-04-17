/*
 * PluginOrganizer.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "PluginOrganizer.h"
#include "logging/Exception.h"
#include "logging/Logger.h"
#include "util/StringUtil.h"
#include "draw/sdl/SimpleCommentFactory.h"
#include "draw/sdl/Renderer.h"

namespace saccubus {

const std::string TAG("PluginOrganizer");

PluginOrganizer::PluginOrganizer(logging::Logger& log, const std::map<std::string, std::string>& config)
:log(log), config(config.begin(), config.end()){
	//デフォルトの値を設定
	// insertは、すでに値がある場合は上書きされない。
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_GRAPHIC, PLUGIN_IMPL_SDL));
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_TEXT, PLUGIN_IMPL_SIMPLE));
	this->config.insert(std::pair<std::string, std::string>(PLUGIN_COMMENT, PLUGIN_IMPL_SIMPLE));
	for(std::map<std::string, std::string>::const_iterator it = config.begin(); it != config.end(); ++it){
		if(util::startsWith(PLUGIN_GRAPHIC_CFG_PREFIX, it->first)){
			this->rendererConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_GRAPHIC_CFG_PREFIX.length()),
							it->second
					));
		}else if(util::startsWith(PLUGIN_TEXT_CFG_PREFIX, it->first)){
			this->commentFactoryConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_TEXT_CFG_PREFIX.length()),
							it->second
					));
		}else if(util::startsWith(PLUGIN_COMMENT_CFG_PREFIX, it->first)){
			this->commentLayerConfig.insert(
					std::pair<std::string, std::string>(
							it->first.substr(PLUGIN_COMMENT_CFG_PREFIX.length()),
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
	if(PLUGIN_IMPL_SDL == config[PLUGIN_GRAPHIC] && PLUGIN_IMPL_SIMPLE == config[PLUGIN_TEXT]){
		draw::sdl::Renderer* _renderer = dynamic_cast<draw::sdl::Renderer*>(renderer);
		if(!_renderer){
			throw logging::Exception(__FILE__, __LINE__,
					"[BUG] Comment factory corresponding to [graphic: %s, text: %s] needs draw::sdl::Renderer*, but got %s",
					config["graphic"].c_str(),
					config["text"].c_str(),
					typeid(renderer).name()
					);
		}
		return new saccubus::draw::sdl::SimpleCommentFactory(log, _renderer);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment factory plugin corresponding to [graphic: %s, text: %s]",
			config["graphic"].c_str(),
			config["text"].c_str()
			);
}
saccubus::draw::Renderer* PluginOrganizer::newRenderer(const int w, const int h)
{
	if(PLUGIN_IMPL_SDL == config[PLUGIN_GRAPHIC]){
		return new saccubus::draw::sdl::Renderer(log, w, h);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no renderer plugin corresponding to [graphic: %s]",
			config["graphic"].c_str()
			);
}
saccubus::layer::CommentLayer* PluginOrganizer::newCommentLayer()
{
	if(PLUGIN_IMPL_SIMPLE == config[PLUGIN_COMMENT]){
		return 0; //FIXME
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment layer plugin corresponding to [graphic: %s]",
			config["comment"].c_str()
			);
}


}
