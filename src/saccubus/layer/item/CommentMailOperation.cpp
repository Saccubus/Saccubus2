/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <functional>
#include <cstdlib>

#include <cinamo/String.h>
#include <nicomo/model/Comment.h>

#include <nekomata/system/System.h>

#include "../../classdefs.h"
#include "Comment.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace layer {
namespace item {

struct Comment::MailOperation{
public:
	enum Permission {
		Normal=0,
		Premium = 1,
		Forked = 2
	};
	enum ArgType {
		Exactly,
		StartsWith
	};
public:
	const enum ArgType argType;
	const std::string name;
	const enum Permission permission;
	typedef std::function<bool(const std::string& name, Comment* comment)> Func;
	const Func func;
	MailOperation(const enum ArgType argType, const std::string& name, const enum Permission permission, Func func)
	:argType(argType), name(name), permission(permission), func(func){};
	virtual ~MailOperation(){};
	bool execute(const std::string& command, Comment* comment) const;
private:
	static bool color_func(const std::string& command, Comment* comment, unsigned int color, unsigned int shadowColor);
	static bool colorCode_func(const std::string& command, Comment* comment);
	static bool size_func(const std::string& command, Comment* comment, item::Comment::Size size);
	static bool placeY_func(const std::string& command, Comment* comment, item::Comment::PlaceY y);
	static bool placeX_func(const std::string& command, Comment* comment, item::Comment::PlaceY y);
	static bool device_func(const std::string& command, Comment* comment, item::Comment::Device device);
	static bool full_func(const std::string& command, Comment* comment);
	static bool sage_func(const std::string& command, Comment* comment);
	static bool invisible_func(const std::string& command, Comment* comment);
	static bool patissier_func(const std::string& command, Comment* comment);
	static bool from_button_func(const std::string& command, Comment* comment);
	static bool is_button_func(const std::string& command, Comment* comment);
	static bool timeCode_func(const std::string& command, Comment* comment);
private:
	static const struct MailOperation Instance[];
	static const size_t Count;
public:
	static bool apply(const std::string& mail, Comment* product);
};

bool Comment::MailOperation::color_func(const std::string& command, Comment* comment, unsigned int color, unsigned int shadowColor)
{
	comment->color(color);
	comment->shadowColor(shadowColor);
	return true;
}

bool Comment::MailOperation::colorCode_func(const std::string& command, Comment* comment)
{
	char* left;
	std::string str = command.substr(1);
	if(str.size() != 6){ /* 六桁のみ受け付ける */
		return false;
	}
	unsigned long c = std::strtoul(str.c_str(), &left,16);
	if(*left != '\0'){ //エラー
		return false;
	}
	comment->color(c);
	if(c == 0x000000){
		comment->shadowColor(0xffffff);
	}else{
		comment->shadowColor(0x000000);
	}
	return true;
}

bool Comment::MailOperation::size_func(const std::string& command, Comment* comment, item::Comment::Size size)
{
	comment->sizeType(size);
	return true;
}

bool Comment::MailOperation::placeY_func(const std::string& command, Comment* comment, item::Comment::PlaceY y)
{
	comment->placeY(y);
	return true;
}

bool Comment::MailOperation::device_func(const std::string& command, Comment* comment, item::Comment::Device device)
{
	comment->device(device);
	return true;
}

bool Comment::MailOperation::full_func(const std::string& command, Comment* comment)
{
	comment->full(true);
	return true;
}
bool Comment::MailOperation::sage_func(const std::string& command, Comment* comment)
{
	comment->sage(true);
	return true;
}
bool Comment::MailOperation::invisible_func(const std::string& command, Comment* comment)
{
	comment->visibility(false);
	return true;
}
bool Comment::MailOperation::patissier_func(const std::string& command, Comment* comment)
{
	comment->patissier(true);
	return true;
}
bool Comment::MailOperation::from_button_func(const std::string& command, Comment* comment)
{
	comment->fromButton(true);
	return true;
}
bool Comment::MailOperation::is_button_func(const std::string& command, Comment* comment)
{
	//comment->isButton(true);
	return true;
}

bool Comment::MailOperation::timeCode_func(const std::string& command, Comment* comment)
{
	char* left;
	std::string str = command.substr(1);
	unsigned long c = std::strtoul(str.c_str(), &left, 10);
	if(*left != '\0'){ //エラー
		return false;
	}
	comment->span(c);
	return true;
}

bool Comment::MailOperation::execute(const std::string& command, Comment* comment) const
{
	if(
		(permission == Comment::MailOperation::Premium && (!comment->isPremium())) ||
		(permission == Comment::MailOperation::Forked && (comment->layer() != item::Comment::Forked))
	){
		return false;
	}
	switch(this->argType){
	case Comment::MailOperation::Exactly:
	{
		if(command == this->name){
			return this->func(command, comment);
		}
		break;
	}
	case Comment::MailOperation::StartsWith:
	{
		if(cinamo::startsWith(command, this->name)){
			return this->func(command, comment);
		}
		break;
	}
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon Comment::MailOperation::Type!!");
	}
	return false;
}

using std::bind;
using saccubus::layer::item::Comment;

const struct Comment::MailOperation Comment::MailOperation::Instance[] = {
		/* カラーコード */
		Comment::MailOperation(Comment::MailOperation::Exactly,    "white",          Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFFFFFF, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "red",            Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFF0000, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "pink",           Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFF8080, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "orange",         Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFFC000, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "yellow",         Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFFFF00, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "green",          Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x00FF00, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "cyan",           Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x00FFFF, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "blue",           Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x0000FF, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "purple",         Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xC000FF, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "black",          Comment::MailOperation::Normal , bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x000000, 0xFFFFFF)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "white2",         Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xCCCC99, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "niconicowhite",  Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xCCCC99, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "red2",           Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xCC0033, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "truered",        Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xCC0033, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "pink2",          Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFF33CC, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "orange2",        Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFF6600, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "passionorange",  Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0xFF6600, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "yello2",         Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x999900, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "madyellow",      Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x999900, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "green2",         Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x00CC66, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "elementalgreen", Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x00CC66, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "cyan2",          Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x00CCCC, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "blue2",          Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x3399FF, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "marineblue",     Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x3399FF, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "purple2",        Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x6633CC, 0x000000)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "nobleviolet",    Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x6633CC, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "black2",         Comment::MailOperation::Premium, bind(color_func, std::placeholders::_1, std::placeholders::_2, 0x666666, 0x000000)),

		Comment::MailOperation(Comment::MailOperation::StartsWith, "#",              Comment::MailOperation::Premium, bind(colorCode_func, std::placeholders::_1, std::placeholders::_2)),

		/* 大きさ */
		Comment::MailOperation(Comment::MailOperation::Exactly,    "small",          Comment::MailOperation::Normal , bind(size_func, std::placeholders::_1, std::placeholders::_2, item::Comment::Small)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "big",            Comment::MailOperation::Normal , bind(size_func, std::placeholders::_1, std::placeholders::_2, item::Comment::Big)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "medium",         Comment::MailOperation::Normal , bind(size_func, std::placeholders::_1, std::placeholders::_2, item::Comment::Medium)),

		/* 位置Y */
		Comment::MailOperation(Comment::MailOperation::Exactly,    "ue",             Comment::MailOperation::Normal , bind(placeY_func, std::placeholders::_1, std::placeholders::_2, item::Comment::Top)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "shita",          Comment::MailOperation::Normal , bind(placeY_func, std::placeholders::_1, std::placeholders::_2, item::Comment::Bottom)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "naka",           Comment::MailOperation::Normal , bind(placeY_func, std::placeholders::_1, std::placeholders::_2, item::Comment::Middle)),

		/* デバイス */
		Comment::MailOperation(Comment::MailOperation::Exactly,    "docomo",         Comment::MailOperation::Normal , bind(device_func, std::placeholders::_1, std::placeholders::_2, item::Comment::docomo)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "iPhone",         Comment::MailOperation::Normal , bind(device_func, std::placeholders::_1, std::placeholders::_2, item::Comment::iPhone)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "softbank",       Comment::MailOperation::Normal , bind(device_func, std::placeholders::_1, std::placeholders::_2, item::Comment::softbank)),

		/* etc */
		Comment::MailOperation(Comment::MailOperation::Exactly,    "full",           Comment::MailOperation::Normal , bind(full_func, std::placeholders::_1, std::placeholders::_2)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "sage",           Comment::MailOperation::Normal , bind(sage_func, std::placeholders::_1, std::placeholders::_2)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "invisible",      Comment::MailOperation::Normal , bind(invisible_func, std::placeholders::_1, std::placeholders::_2)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "patissier",      Comment::MailOperation::Normal , bind(patissier_func, std::placeholders::_1, std::placeholders::_2)),

		Comment::MailOperation(Comment::MailOperation::Exactly,    "from_button",    Comment::MailOperation::Normal , bind(from_button_func, std::placeholders::_1, std::placeholders::_2)),
		Comment::MailOperation(Comment::MailOperation::Exactly,    "is_button",      Comment::MailOperation::Normal , bind(is_button_func, std::placeholders::_1, std::placeholders::_2)),

		/*
		 * 投稿者コメントだけ！
		 */

		/* 表示時間 */
		Comment::MailOperation(Comment::MailOperation::StartsWith, "@",              Comment::MailOperation::Forked , bind(timeCode_func, std::placeholders::_1, std::placeholders::_2)),
};
const size_t Comment::MailOperation::Count = sizeof(Instance)/sizeof(Comment::MailOperation);

bool Comment::MailOperation::apply(const std::string& mail, Comment* product)
{
	for(size_t i = 0;i < MailOperation::Count;++i){
		const MailOperation* cmd = &MailOperation::Instance[i];
		if(cmd->execute(mail, product)){
			return true;
		}
	}
	return false;
}

bool Comment::applyMail(const std::string& ml)
{
	return MailOperation::apply(ml, this);
}

}}}


