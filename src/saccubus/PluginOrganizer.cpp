/*
 * PluginOrganizer.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "PluginOrganizer.h"
#include "logging/Exception.h"

#include "draw/sdl/SimpleCommentFactory.h"
#include "draw/sdl/ImageFactory.h"

namespace saccubus {

PluginOrganizer::PluginOrganizer(const std::map<std::string, std::string>& config)
:config(config.begin(), config.end()){
	//デフォルトの値を設定
	// insertは、すでに値がある場合は上書きされない。
	this->config.insert(std::pair<std::string, std::string>("graphic", "sdl"));
	this->config.insert(std::pair<std::string, std::string>("text", "simple"));
	this->config.insert(std::pair<std::string, std::string>("comment", "simple"));

}

PluginOrganizer::~PluginOrganizer() {
	// TODO Auto-generated destructor stub
}

saccubus::draw::CommentFactory* PluginOrganizer::newCommentFactory(draw::ImageFactory* const imgFactory)
{
	if(PLUGIN_SDL == config["graphic"] && PLUGIN_SIMPLE == config["text"]){
		draw::sdl::ImageFactory* _imgFactory = dynamic_cast<draw::sdl::ImageFactory*>(imgFactory);
		if(!_imgFactory){
			throw logging::Exception(__FILE__, __LINE__,
					"[BUG] Comment factory corresponding to [graphic: %s, text: %s] needs draw::sdl::ImageFactory*, but got %s",
					config["graphic"].c_str(),
					config["text"].c_str(),
					typeid(imgFactory).name()
					);
		}
		return new saccubus::draw::sdl::SimpleCommentFactory(_imgFactory);
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment factory plugin corresponding to [graphic: %s, text: %s]",
			config["graphic"].c_str(),
			config["text"].c_str()
			);
}
saccubus::draw::ImageFactory* PluginOrganizer::newImageFactory()
{
	if(PLUGIN_SDL == config["graphic"]){
		return new saccubus::draw::sdl::ImageFactory();
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no sprite factory plugin corresponding to [graphic: %s]",
			config["graphic"].c_str()
			);
}
saccubus::layer::CommentLayer* PluginOrganizer::newCommentLayer()
{
	if(PLUGIN_SIMPLE == config["comment"]){
		return 0; //FIXME
	}
	throw logging::Exception(__FILE__, __LINE__,
			"There is no comment layer plugin corresponding to [graphic: %s]",
			config["comment"].c_str()
			);
}


}
