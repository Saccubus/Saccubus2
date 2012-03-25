/*
 * ReplaceTable.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include <sstream>
#include "ReplaceTable.h"
#include "../util/Bundle.h"
#include "../util/StringUtil.h"

namespace saccubus {
namespace meta {

ReplaceTable::ReplaceTable(const std::string& entry) {
	std::istringstream ss(entry);
	std::string elem;
	//FIXME: FormEncoded形式だが、オーダーを保存しなければならないので、自分でパース…。
	while(std::getline(ss, elem, '&')){
		size_t center = elem.find('=');
		std::string from(util::decodePercent(elem.substr(0, center)));
		std::string to(util::decodePercent(elem.substr(center+1)));
		if(from.at(0) == '*'){
			replaceList.push_back(new ReplaceItem(from.substr(1), to, true));
		}else{
			replaceList.push_back(new ReplaceItem(from, to, false));
		}
	}
}

ReplaceTable::~ReplaceTable() {
	for(std::vector<const ReplaceItem*>::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it){
		delete *it;
	}
	replaceList.clear();
}

std::string ReplaceTable::replace(const std::string& target) const
{
	std::string replaced(target);
	for(std::vector<const ReplaceItem*>::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it){
		replaced = (*it)->replace(replaced);
	}
	return replaced;
}

}}
