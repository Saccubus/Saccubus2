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

#include <sstream>
#include <cinamo/Url.h>
#include <nicomo/model/ReplaceTable.h>

namespace nicomo {
namespace model {

ReplaceTable::ReplaceTable(const std::string& entry) {
	std::istringstream ss(entry);
	std::string elem;
	//FIXME:  FormEncoded形式だが、オーダーを保存しなければならないので、自分でパース…。
	while(std::getline(ss, elem, '&')){
		size_t center = elem.find('=');
		std::string from(cinamo::url::decodeForm(elem.substr(0, center)));
		std::string to(cinamo::url::decodeForm(elem.substr(center+1)));
		if(from.at(0) == '*'){
			replaceList.insert(replaceList.begin(), new ReplaceItem(from.substr(1), to, true));
		}else{
			replaceList.insert(replaceList.begin(), new ReplaceItem(from, to, false));
		}
	}
}

ReplaceTable::~ReplaceTable() {
	for(std::vector<const ReplaceItem*>::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it){
		delete *it;
	}
	decltype(this->replaceList)().swap(this->replaceList);
}

std::string ReplaceTable::replace(const std::string& target) const
{
	std::string replaced(target);
	for(std::vector<const ReplaceItem*>::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it){
		const ReplaceItem* const obj = *it;
		replaced = obj->replace(replaced);
	}
	return replaced;
}

}}
