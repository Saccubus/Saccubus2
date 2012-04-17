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
#include "CommentProcessingFlow.h"
#include "../../meta/Comment.h"
#include "../../util/StringUtil.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace layer {
namespace item {

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

bool MailOperation::execute(const std::string& command, Comment* comment) const
{
	if((permission & Premium) == Premium){
		if(!comment->orig()->premium()){
			return false;
		}
	}
	switch(this->argType){
	case MailOperation::Exactly:
	{
		if(command == this->name){
			return this->func(command, comment);
		}
		break;
	}
	case MailOperation::StartsWith:
	{
		if(util::startsWith(command, this->name)){
			return this->func(command, comment);
		}
		break;
	}
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon MailOperation::Type!!");
	}
	return false;
}

using namespace std::tr1;
using namespace std::tr1::placeholders;
using saccubus::layer::item::Comment;

const struct MailOperation MailOperation::Instance[] = {
		/* カラーコード */
		MailOperation(MailOperation::Exactly,    "white",          MailOperation::Normal , bind(color_func, _1, _2, 0xFFFFFF, 0x000000)),
		MailOperation(MailOperation::Exactly,    "red",            MailOperation::Normal , bind(color_func, _1, _2, 0xFF0000, 0x000000)),
		MailOperation(MailOperation::Exactly,    "pink",           MailOperation::Normal , bind(color_func, _1, _2, 0xFF8080, 0x000000)),
		MailOperation(MailOperation::Exactly,    "orange",         MailOperation::Normal , bind(color_func, _1, _2, 0xFFC000, 0x000000)),
		MailOperation(MailOperation::Exactly,    "yellow",         MailOperation::Normal , bind(color_func, _1, _2, 0xFFFF00, 0x000000)),
		MailOperation(MailOperation::Exactly,    "green",          MailOperation::Normal , bind(color_func, _1, _2, 0x00FF00, 0x000000)),
		MailOperation(MailOperation::Exactly,    "cyan",           MailOperation::Normal , bind(color_func, _1, _2, 0x00FFFF, 0x000000)),
		MailOperation(MailOperation::Exactly,    "blue",           MailOperation::Normal , bind(color_func, _1, _2, 0x0000FF, 0x000000)),
		MailOperation(MailOperation::Exactly,    "purple",         MailOperation::Normal , bind(color_func, _1, _2, 0xC000FF, 0x000000)),
		MailOperation(MailOperation::Exactly,    "black",          MailOperation::Normal , bind(color_func, _1, _2, 0x000000, 0xFFFFFF)),

		MailOperation(MailOperation::Exactly,    "white2",         MailOperation::Premium, bind(color_func, _1, _2, 0xCCCC99, 0x000000)),
		MailOperation(MailOperation::Exactly,    "niconicowhite",  MailOperation::Premium, bind(color_func, _1, _2, 0xCCCC99, 0x000000)),

		MailOperation(MailOperation::Exactly,    "red2",           MailOperation::Premium, bind(color_func, _1, _2, 0xCC0033, 0x000000)),
		MailOperation(MailOperation::Exactly,    "truered",        MailOperation::Premium, bind(color_func, _1, _2, 0xCC0033, 0x000000)),

		MailOperation(MailOperation::Exactly,    "pink2",          MailOperation::Premium, bind(color_func, _1, _2, 0xFF33CC, 0x000000)),

		MailOperation(MailOperation::Exactly,    "orange2",        MailOperation::Premium, bind(color_func, _1, _2, 0xFF6600, 0x000000)),
		MailOperation(MailOperation::Exactly,    "passionorange",  MailOperation::Premium, bind(color_func, _1, _2, 0xFF6600, 0x000000)),

		MailOperation(MailOperation::Exactly,    "yello2",         MailOperation::Premium, bind(color_func, _1, _2, 0x999900, 0x000000)),
		MailOperation(MailOperation::Exactly,    "madyellow",      MailOperation::Premium, bind(color_func, _1, _2, 0x999900, 0x000000)),

		MailOperation(MailOperation::Exactly,    "green2",         MailOperation::Premium, bind(color_func, _1, _2, 0x00CC66, 0x000000)),
		MailOperation(MailOperation::Exactly,    "elementalgreen", MailOperation::Premium, bind(color_func, _1, _2, 0x00CC66, 0x000000)),

		MailOperation(MailOperation::Exactly,    "cyan2",          MailOperation::Premium, bind(color_func, _1, _2, 0x00CCCC, 0x000000)),

		MailOperation(MailOperation::Exactly,    "blue2",          MailOperation::Premium, bind(color_func, _1, _2, 0x3399FF, 0x000000)),
		MailOperation(MailOperation::Exactly,    "marineblue",     MailOperation::Premium, bind(color_func, _1, _2, 0x3399FF, 0x000000)),

		MailOperation(MailOperation::Exactly,    "purple2",        MailOperation::Premium, bind(color_func, _1, _2, 0x6633CC, 0x000000)),
		MailOperation(MailOperation::Exactly,    "nobleviolet",    MailOperation::Premium, bind(color_func, _1, _2, 0x6633CC, 0x000000)),

		MailOperation(MailOperation::Exactly,    "black2",         MailOperation::Premium, bind(color_func, _1, _2, 0x666666, 0x000000)),

		MailOperation(MailOperation::StartsWith, "#",              MailOperation::Premium, bind(colorCode_func, _1, _2)),

		/* 大きさ */
		MailOperation(MailOperation::Exactly,    "small",          MailOperation::Normal , bind(size_func, _1, _2, Comment::Small)),
		MailOperation(MailOperation::Exactly,    "big",            MailOperation::Normal , bind(size_func, _1, _2, Comment::Big)),
		MailOperation(MailOperation::Exactly,    "medium",         MailOperation::Normal , bind(size_func, _1, _2, Comment::Medium)),

		/* 位置Y */
		MailOperation(MailOperation::Exactly,    "ue",             MailOperation::Normal , bind(placeY_func, _1, _2, Comment::Top)),
		MailOperation(MailOperation::Exactly,    "shita",          MailOperation::Normal , bind(placeY_func, _1, _2, Comment::Bottom)),
		MailOperation(MailOperation::Exactly,    "naka",           MailOperation::Normal , bind(placeY_func, _1, _2, Comment::Middle)),

		/* デバイス */
		MailOperation(MailOperation::Exactly,    "docomo",         MailOperation::Normal , bind(device_func, _1, _2, Comment::docomo)),
		MailOperation(MailOperation::Exactly,    "iPhone",         MailOperation::Normal , bind(device_func, _1, _2, Comment::iPhone)),
		MailOperation(MailOperation::Exactly,    "softbank",       MailOperation::Normal , bind(device_func, _1, _2, Comment::softbank)),

		/* etc */
		MailOperation(MailOperation::Exactly,    "full",           MailOperation::Normal , bind(full_func, _1, _2)),
		MailOperation(MailOperation::Exactly,    "sage",           MailOperation::Normal , bind(sage_func, _1, _2)),
		MailOperation(MailOperation::Exactly,    "invisible",      MailOperation::Normal , bind(invisible_func, _1, _2)),
		MailOperation(MailOperation::Exactly,    "patissier",      MailOperation::Normal , bind(patissier_func, _1, _2)),

		MailOperation(MailOperation::Exactly,    "from_button",    MailOperation::Normal , bind(from_button_func, _1, _2)),
		MailOperation(MailOperation::Exactly,    "is_button",      MailOperation::Normal , bind(is_button_func, _1, _2)),
};
const size_t MailOperation::Count = sizeof(Instance)/sizeof(MailOperation);


bool MailOperation::apply(const std::string& mail, Comment* product)
{
	for(size_t i = 0;i < Count;++i){
		const MailOperation* cmd = &Instance[i];
		if(cmd->execute(mail, product)){
			return true;
		}
	}
	return false;
}
}}}


