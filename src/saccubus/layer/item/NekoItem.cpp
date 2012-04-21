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

#include "NekoItem.h"
#include "../../util/StringUtil.h"

namespace saccubus {
namespace layer {
namespace item {

NekoItem::NekoItem(nekomata::system::Drawable* nekoDrawable)
{
	this->drawable(nekoDrawable);
}

NekoItem::~NekoItem() {
}

void NekoItem::invalidate()
{
	std::vector<std::string> posList;
	util::splitSpace(drawable()->pos(), posList);
	this->posX(CenterX);
	this->posY(CenterY);
	for(std::vector<std::string>::const_iterator it = posList.begin(); it != posList.end(); ++it)
	{
		if("migi" == *it){
			this->posX(Right);
		}else if("hidari" == *it){
			this->posX(Left);
		}else if("ue" == *it){
			this->posY(Top);
		}else if("shita" == *it){
			this->posY(Bottom);
		}
	}
	this->Item::invalidate();
}


}}}
