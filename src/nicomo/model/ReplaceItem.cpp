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
