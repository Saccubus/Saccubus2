/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "NekoItem.h"
#include <cinamo/String.h>

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
	std::vector<std::string> posList( cinamo::splitSpace(drawable()->pos()) );
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
