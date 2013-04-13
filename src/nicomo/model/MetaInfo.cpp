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
#include <cinamo/XMLAttrParser.h>
#include <nicomo/model/MetaInfo.h>

namespace nicomo {
namespace model {

const static std::string TAG("MetaInfo");

MetaInfo::MetaInfo(cinamo::Logger& log, tinyxml2::XMLElement* elm)
{
	read(log, elm);
}

MetaInfo::MetaInfo(cinamo::Logger& log, tinyxml2::XMLDocument* doc)
{
	read(log, doc->RootElement());
}

MetaInfo::MetaInfo(cinamo::Logger& log, const std::string& filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());
	read(log, doc.RootElement());
}

void MetaInfo::read(cinamo::Logger& log, tinyxml2::XMLElement* elm)
{
	std::string stat;
	cinamo::xml::parseAttr("status", stat, std::string(""), elm);
	if(std::string("nicovideo_thumb_response") != elm->Name() || stat != "ok"){
		log.w(TAG, "Invalid meta info: status: %s:%s", elm->Name(), stat.c_str());
		return;
	}
	tinyxml2::XMLElement* thumbNode = elm->FirstChildElement("thumb");
	if(!thumbNode){
		log.w(TAG, "Meta info does not contain 'thumb' element.");
		return;
	}
	tinyxml2::XMLElement* titleNode = thumbNode->FirstChildElement("title");
	if(titleNode){
		this->title(titleNode->GetText());
	}
	if(log.t()){
		log.t(TAG, "Title:%s",
			this->title().c_str()
		);
	}
}


}}
