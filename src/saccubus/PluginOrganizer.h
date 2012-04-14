/*
 * PluginOrganizer.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef PLUGINORGANIZER_H_
#define PLUGINORGANIZER_H_

#include <map>
#include <string>
#include "classdefs.h"

namespace saccubus {

/**
 * プラグインの生成（依存性注入）を行う。
 * スイッチ付きのFactoryメソッドと思えばよろしい。
 */
class PluginOrganizer {
private:
	std::map<std::string, std::string> config;
public:
	PluginOrganizer(const std::map<std::string, std::string>& config);
	virtual ~PluginOrganizer();
public:
	draw::Canvas* newCanvas();
	draw::SpriteFactory* newSpriteFactory();
	draw::CommentFactory* newCommentFactory();
	layer::CommentLayer* newCommentLayer();
};

}
#endif /* PLUGINORGANIZER_H_ */
