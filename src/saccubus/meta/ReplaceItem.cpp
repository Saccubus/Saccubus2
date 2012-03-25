/*
 * ReplaceItem.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "ReplaceItem.h"

namespace saccubus {
namespace meta {

ReplaceItem::ReplaceItem(const std::string& from, const std::string& to, bool whole)
:from_(from), to_(to), whole_(whole)
{
}
ReplaceItem::ReplaceItem(const ReplaceItem& other)
:from_(other.from()), to_(other.to()), whole_(other.whole())
{

}

ReplaceItem::~ReplaceItem() {
}
std::string ReplaceItem::from() const
{
	return from_;
}
std::string ReplaceItem::to() const
{
	return to_;
}
bool ReplaceItem::whole() const
{
	return whole_;
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
