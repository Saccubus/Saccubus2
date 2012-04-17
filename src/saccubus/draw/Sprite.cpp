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

#include "Sprite.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

Sprite::Sprite(logging::Logger& log)
:log(log), refcount(0)
{
}

Sprite::~Sprite() {
}


void Sprite::incref()
{
	this->refcount++;
}
void Sprite::decref()
{
	this->refcount--;
	if(this->refcount < 0){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] RawSprite::Handler refcount = %d < 0", this->refcount);
	}else if(this->refcount == 0){
		this->onFree();
	}
}

}}
