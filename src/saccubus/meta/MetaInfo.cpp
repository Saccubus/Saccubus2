/*
 * MetaInfo.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "../logging/Logger.h"
#include "MetaInfo.h"
#include "Util.h"

namespace saccubus {
namespace meta {

const static std::string TAG("MetaInfo");

MetaInfo::MetaInfo(logging::Logger& log, xmlNode* node)
{
	read(log, node);
}

MetaInfo::MetaInfo(logging::Logger& log, xmlDoc* doc)
{
	xmlNode* root = xmlDocGetRootElement(doc);
	read(log, root);
}

MetaInfo::MetaInfo(logging::Logger& log, const std::string& filename)
{
	xmlDoc* doc = xmlReadFile(filename.c_str(), NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	read(log, root);
	xmlFreeDoc(doc);
}

MetaInfo::~MetaInfo() {
}

void MetaInfo::read(logging::Logger& log, xmlNode* node)
{
	std::string stat = readNodeProp(node, "status", "");
	if(compareNodeName(node, "nicovideo_thumb_response") || stat != "ok"){
		log.w(TAG, "Invalid meta info: status: %s", stat.c_str());
		return;
	}
	xmlNode* thumbNode = node->children;
	if(compareNodeName(thumbNode, "thumb")){
		log.w(TAG, "Invalid meta info XML: child: %s", thumbNode->name);
		return;
	}
	for(xmlNode* child = thumbNode->children; child != thumbNode->last; ++child){
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
