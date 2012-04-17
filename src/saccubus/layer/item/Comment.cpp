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

#include "Comment.h"
#include <cmath>
#include "../../meta/Comment.h"

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("context/Comment");

Comment::Comment()
{
	this->orig(0);
	this->setDefault();
}
Comment::Comment(logging::Logger& log, const meta::Comment* comment)
{
	this->orig(comment);
	this->setDefault();
	this->interpret(log);
}

Comment::~Comment() {
}

void Comment::setDefault()
{
	this->message(orig() ? orig()->message() : "");
	this->from(orig() ? orig()->vpos()-1.0f : NAN);
	this->to(orig() ? orig()->vpos()+2.0f : NAN);
	this->isButton(false);
	this->fromButton(false);
	this->full(false);
	this->sage(true);
	this->patissier(false);
	this->device(Comment::Unspecified);
	this->visibility(true);
	this->size(Comment::Medium);
	this->placeX(Comment::Center);
	this->placeY(Comment::Middle);
	this->color(0xFFFFFF);
	this->shadowColor(0x000000);
}

void Comment::interpret(logging::Logger& log)
{
	for(meta::Comment::MailIterator it= this->orig()->mailBegin(); it != this->orig()->mailEnd(); ++it){
		if(!Comment::interpret(*it, this))
		{
			log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}
}


}}}
