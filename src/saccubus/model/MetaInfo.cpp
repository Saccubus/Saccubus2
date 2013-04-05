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

#include <cinamo/Logger.h>
#include "MetaInfo.h"
#include "Util.h"

namespace saccubus {
namespace model {

const static std::string TAG("MetaInfo");

MetaInfo::MetaInfo(cinamo::Logger& log, xmlNode* node)
{
	read(log, node);
}

MetaInfo::MetaInfo(cinamo::Logger& log, xmlDoc* doc)
{
	xmlNode* root = xmlDocGetRootElement(doc);
	read(log, root);
}

MetaInfo::MetaInfo(cinamo::Logger& log, const std::string& filename)
{
	xmlDoc* doc = xmlReadFile(filename.c_str(), NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	read(log, root);
	xmlFreeDoc(doc);
}

MetaInfo::~MetaInfo() {
}

void MetaInfo::read(cinamo::Logger& log, xmlNode* node)
{
	std::string stat = readNodeProp(node, "status", "");
	if(!compareNodeName(node, "nicovideo_thumb_response") || stat != "ok"){
		log.w(TAG, "Invalid meta info: status: %s", stat.c_str());
		return;
	}
	xmlNode* thumbNode = 0;
	for(thumbNode = node->children; thumbNode; thumbNode=thumbNode->next){
		if(compareNodeName(thumbNode, "thumb")){
			break;
		}
	}
	if(!thumbNode){
		log.w(TAG, "Meta info does not contain 'thumb' element.");
		return;
	}
	for(xmlNode* child = thumbNode->children; child; child=child->next){
		if(compareNodeName(child, "title")){
			this->title(readNodeContent(child));
		}
	}
	if(log.t()){
		log.t(TAG, "Title:%s",
			this->title().c_str()
		);
	}
}


}}
