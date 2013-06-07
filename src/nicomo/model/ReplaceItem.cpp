/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include <nicomo/model/ReplaceItem.h>

namespace nicomo {
namespace model {

ReplaceItem::ReplaceItem(const std::string& from, const std::string& to, bool whole)
:from_(from), to_(to), whole_(whole)
{
}
ReplaceItem::ReplaceItem(const ReplaceItem& other)
:from_(other.from()), to_(other.to()), whole_(other.whole())
{

}
std::string ReplaceItem::replace(const std::string& target) const
{
	if(whole()){
		if(target.find(from()) != std::string::npos){
			return to();
		}else{
			return target;
		}
	}else{
		std::string replaced(target);
		std::string::size_type pos = 0;
		while(pos = replaced.find(from(), pos), pos != std::string::npos){
			replaced.replace(pos, from().length(), to());
			pos += to().length();
		}
		return replaced;
	}
}

}}
