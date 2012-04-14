/*
 * PluginOrganizer.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "PluginOrganizer.h"

namespace saccubus {

PluginOrganizer::PluginOrganizer(const std::map<std::string, std::string>& config)
:config(config.begin(), config.end()){
	//デフォルトの値を設定
	// insertは、すでに値がある場合は上書きされない。
	this->config.insert(std::pair<std::string, std::string>("comment", "simple"));
	this->config.insert(std::pair<std::string, std::string>("text", "simple"));

}

PluginOrganizer::~PluginOrganizer() {
	// TODO Auto-generated destructor stub
}

}
