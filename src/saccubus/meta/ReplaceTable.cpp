/*
 * ReplaceTable.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "ReplaceTable.h"
#include "../util/Bundle.h"

namespace saccubus {
namespace meta {

ReplaceTable::ReplaceTable(const std::string& entry) {
	util::Bundle bun = util::Bundle::fromFormEncoded(entry);
	for(util::Bundle::Iterator it = bun.begin();it != bun.end();++it){
		std::string to(it->second);
		if(to.at(0) == '*'){
			replaceList.push_back(new ReplaceItem(it->first, to.substr(1), true));
		}else{
			replaceList.push_back(new ReplaceItem(it->first, to, false));
		}
	}
}

ReplaceTable::~ReplaceTable() {
	for(std::vector<const ReplaceItem*>::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it){
		delete *it;
	}
	replaceList.clear();
}

}}
