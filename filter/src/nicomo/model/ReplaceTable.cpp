/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include <sstream>
#include <cinamo/Url.h>
#include <nicomo/model/ReplaceTable.h>

namespace nicomo {
namespace model {

ReplaceTable::ReplaceTable(std::string const& entry) {
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

std::string ReplaceTable::replace(std::string const& target) const
{
	std::string replaced(target);
	for(std::vector<const ReplaceItem*>::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it){
		const ReplaceItem* const obj = *it;
		replaced = obj->replace(replaced);
	}
	return replaced;
}

}}
