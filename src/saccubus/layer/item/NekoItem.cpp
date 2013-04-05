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
:_posX(UndefinedX), _posY(UndefinedY)
{
	this->drawable(nekoDrawable);
}

void NekoItem::reload()
{
	std::vector<std::string> posList;
	util::splitSpace(drawable()->pos(), posList);
	_posX = CenterX;
	_posY = CenterY;
	for(std::vector<std::string>::const_iterator it = posList.begin(); it != posList.end(); ++it)
	{
		if("migi" == *it){
			_posX = Right;
		}else if("hidari" == *it){
			_posX = Left;
		}else if("ue" == *it){
			_posY = Top;
		}else if("shita" == *it){
			_posY = Bottom;
		}else if("naka" == *it){
			_posY = CenterY;
		}
	}
}
void NekoItem::invalidate()
{
	_posX = UndefinedX;
	_posY = UndefinedY;
	this->Item::invalidate();
}
enum NekoItem::PosX NekoItem::posX()
{
	if(_posX == UndefinedX){
		this->reload();
	}
	return _posX;
}
enum NekoItem::PosY NekoItem::posY()
{
	if(_posY == UndefinedY){
		this->reload();
	}
	return _posY;
}


}}}
