/*
 * CommentCommand.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include <cstdlib>
#include "Comment.h"
#include "../meta/Comment.h"
#include "../util/StringUtil.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace context {

static void color_func(const std::string& command, Comment* comment, unsigned int color, unsigned int shadowColor)
{
	comment->color(color);
	comment->shadowColor(shadowColor);
}

static void colorCode_func(const std::string& command, Comment* comment)
{
	char* left;
	unsigned long c = std::strtoul(command.substr(1).c_str(), &left,16);
	if(*left != '\0'){ //エラー
		//FIXME: エラーハンドリング
	}
	comment->color(c);
	comment->shadowColor(0x000000);
}

static void size_func(const std::string& command, Comment* comment, Comment::Size size)
{
	comment->size(size);
}
/*
 * FIXME: 使われてない？
static void placeX_func(const std::string& command, Comment* comment, Comment::PlaceX x)
{
	comment->placeX(x);
}
*/
static void placeY_func(const std::string& command, Comment* comment, Comment::PlaceY y)
{
	comment->placeY(y);
}

static void device_func(const std::string& command, Comment* comment, Comment::Device device)
{
	comment->device(device);
}

static void full_func(const std::string& command, Comment* comment)
{
	comment->full(true);
}
static void sage_func(const std::string& command, Comment* comment)
{
	comment->sage(true);
}
static void invisible_func(const std::string& command, Comment* comment){
	comment->visibility(false);
}
static void patissier_func(const std::string& command, Comment* comment){
	comment->patissier(true);
}
static void from_button_func(const std::string& command, Comment* comment){
	comment->fromButton(true);
}
static void is_button_func(const std::string& command, Comment* comment){
	comment->isButton(true);
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
			this->func(command, comment);
			return true;
		}
		break;
	}
	case Comment::Command::StartsWith:
	{
		if(util::startsWith(command, this->name)){
			this->func(command, comment);
			return true;
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


