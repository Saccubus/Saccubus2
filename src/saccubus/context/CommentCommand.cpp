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

#include <cstdlib>
#include "Comment.h"
#include "../meta/Comment.h"
#include "../util/StringUtil.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace context {

static bool color_func(const std::string& command, Comment* comment, unsigned int color, unsigned int shadowColor)
{
	comment->color(color);
	comment->shadowColor(shadowColor);
	return true;
}

static bool colorCode_func(const std::string& command, Comment* comment)
{
	char* left;
	unsigned long c = std::strtoul(command.substr(1).c_str(), &left,16);
	if(*left != '\0'){ //エラー
		return false;
	}
	comment->color(c);
	comment->shadowColor(0x000000);
	return true;
}

static bool size_func(const std::string& command, Comment* comment, Comment::Size size)
{
	comment->size(size);
	return true;
}
/*
 * TODO: 使われてない？
static bool placeX_func(const std::string& command, Comment* comment, Comment::PlaceX x)
{
	comment->placeX(x);
	return true;
}
*/
static bool placeY_func(const std::string& command, Comment* comment, Comment::PlaceY y)
{
	comment->placeY(y);
	return true;
}

static bool device_func(const std::string& command, Comment* comment, Comment::Device device)
{
	comment->device(device);
	return true;
}

static bool full_func(const std::string& command, Comment* comment)
{
	comment->full(true);
	return true;
}
static bool sage_func(const std::string& command, Comment* comment)
{
	comment->sage(true);
	return true;
}
static bool invisible_func(const std::string& command, Comment* comment){
	comment->visibility(false);
	return true;
}
static bool patissier_func(const std::string& command, Comment* comment){
	comment->patissier(true);
	return true;
}
static bool from_button_func(const std::string& command, Comment* comment){
	comment->fromButton(true);
	return true;
}
static bool is_button_func(const std::string& command, Comment* comment){
	comment->isButton(true);
	return true;
}

bool Comment::Command::execute(const std::string& command, Comment* comment) const
{
	if((permission & Premium) == Premium){
		if(!comment->orig()->premium()){
			return false;
		}
	}
	switch(this->argType){
	case Comment::Command::Exactly:
	{
		if(command == this->name){
			return this->func(command, comment);
		}
		break;
	}
	case Comment::Command::StartsWith:
	{
		if(util::startsWith(command, this->name)){
			return this->func(command, comment);
		}
		break;
	}
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon Comment::Command::Type!!");
	}
	return false;
}

using namespace std::tr1;
using namespace std::tr1::placeholders;
using saccubus::context::Comment;

const struct Comment::Command Comment::Commands[] = {
		/* カラーコード */
		Comment::Command(Comment::Command::Exactly,    "white",          Comment::Command::Normal , bind(color_func, _1, _2, 0xFFFFFF, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "red",            Comment::Command::Normal , bind(color_func, _1, _2, 0xFF0000, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "pink",           Comment::Command::Normal , bind(color_func, _1, _2, 0xFF8080, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "orange",         Comment::Command::Normal , bind(color_func, _1, _2, 0xFFC000, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "yellow",         Comment::Command::Normal , bind(color_func, _1, _2, 0xFFFF00, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "green",          Comment::Command::Normal , bind(color_func, _1, _2, 0x00FF00, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "cyan",           Comment::Command::Normal , bind(color_func, _1, _2, 0x00FFFF, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "blue",           Comment::Command::Normal , bind(color_func, _1, _2, 0x0000FF, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "purple",         Comment::Command::Normal , bind(color_func, _1, _2, 0xC000FF, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "black",          Comment::Command::Normal , bind(color_func, _1, _2, 0x000000, 0xFFFFFF)),

		Comment::Command(Comment::Command::Exactly,    "white2",         Comment::Command::Premium, bind(color_func, _1, _2, 0xCCCC99, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "niconicowhite",  Comment::Command::Premium, bind(color_func, _1, _2, 0xCCCC99, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "red2",           Comment::Command::Premium, bind(color_func, _1, _2, 0xCC0033, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "truered",        Comment::Command::Premium, bind(color_func, _1, _2, 0xCC0033, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "pink2",          Comment::Command::Premium, bind(color_func, _1, _2, 0xFF33CC, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "orange2",        Comment::Command::Premium, bind(color_func, _1, _2, 0xFF6600, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "passionorange",  Comment::Command::Premium, bind(color_func, _1, _2, 0xFF6600, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "yello2",         Comment::Command::Premium, bind(color_func, _1, _2, 0x999900, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "madyellow",      Comment::Command::Premium, bind(color_func, _1, _2, 0x999900, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "green2",         Comment::Command::Premium, bind(color_func, _1, _2, 0x00CC66, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "elementalgreen", Comment::Command::Premium, bind(color_func, _1, _2, 0x00CC66, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "cyan2",          Comment::Command::Premium, bind(color_func, _1, _2, 0x00CCCC, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "blue2",          Comment::Command::Premium, bind(color_func, _1, _2, 0x3399FF, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "marineblue",     Comment::Command::Premium, bind(color_func, _1, _2, 0x3399FF, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "purple2",        Comment::Command::Premium, bind(color_func, _1, _2, 0x6633CC, 0x000000)),
		Comment::Command(Comment::Command::Exactly,    "nobleviolet",    Comment::Command::Premium, bind(color_func, _1, _2, 0x6633CC, 0x000000)),

		Comment::Command(Comment::Command::Exactly,    "black2",         Comment::Command::Premium, bind(color_func, _1, _2, 0x666666, 0x000000)),

		Comment::Command(Comment::Command::StartsWith, "#",              Comment::Command::Premium, bind(colorCode_func, _1, _2)),

		/* 大きさ */
		Comment::Command(Comment::Command::Exactly,    "small",          Comment::Command::Normal , bind(size_func, _1, _2, Comment::Small)),
		Comment::Command(Comment::Command::Exactly,    "big",            Comment::Command::Normal , bind(size_func, _1, _2, Comment::Big)),
		Comment::Command(Comment::Command::Exactly,    "medium",         Comment::Command::Normal , bind(size_func, _1, _2, Comment::Medium)),

		/* 位置Y */
		Comment::Command(Comment::Command::Exactly,    "ue",             Comment::Command::Normal , bind(placeY_func, _1, _2, Comment::Top)),
		Comment::Command(Comment::Command::Exactly,    "shita",          Comment::Command::Normal , bind(placeY_func, _1, _2, Comment::Bottom)),
		Comment::Command(Comment::Command::Exactly,    "naka",           Comment::Command::Normal , bind(placeY_func, _1, _2, Comment::Middle)),

		/* デバイス */
		Comment::Command(Comment::Command::Exactly,    "docomo",         Comment::Command::Normal , bind(device_func, _1, _2, Comment::docomo)),
		Comment::Command(Comment::Command::Exactly,    "iPhone",         Comment::Command::Normal , bind(device_func, _1, _2, Comment::iPhone)),
		Comment::Command(Comment::Command::Exactly,    "softbank",       Comment::Command::Normal , bind(device_func, _1, _2, Comment::softbank)),

		/* etc */
		Comment::Command(Comment::Command::Exactly,    "full",           Comment::Command::Normal , bind(full_func, _1, _2)),
		Comment::Command(Comment::Command::Exactly,    "sage",           Comment::Command::Normal , bind(sage_func, _1, _2)),
		Comment::Command(Comment::Command::Exactly,    "invisible",      Comment::Command::Normal , bind(invisible_func, _1, _2)),
		Comment::Command(Comment::Command::Exactly,    "patissier",      Comment::Command::Normal , bind(patissier_func, _1, _2)),

		Comment::Command(Comment::Command::Exactly,    "from_button",    Comment::Command::Normal , bind(from_button_func, _1, _2)),
		Comment::Command(Comment::Command::Exactly,    "is_button",      Comment::Command::Normal , bind(is_button_func, _1, _2)),
};
const size_t Comment::CommandsSize = sizeof(Comment::Commands)/sizeof(Comment::Command);

bool Comment::interpret(const std::string& command, Comment* comment)
{
	for(size_t i = 0;i < Comment::CommandsSize;++i){
		const Comment::Command* cmd = &Comment::Commands[i];
		if(cmd->execute(command, comment)){
			return true;
		}
	}
	return false;

}

}}


