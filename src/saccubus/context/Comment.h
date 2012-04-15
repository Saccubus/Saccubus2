/*
 * Comment.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef CONTEXT_COMMENT_H_
#define CONTEXT_COMMENT_H_

#include <string>
#include <tr1/memory>
#include <tr1/functional>
#include "../classdefs.h"
#include "../util/ClassAccessor.h"

namespace nekomata{
namespace system{
class Comment;
}}
namespace saccubus {
namespace context {


class Comment {
private:
	static const struct Command{
	public:
		enum Type{
			Normal=0,
			Premium = 1,
		};
		enum ArgType{
			Exactly,
			StartsWith
		};
	public:
		const enum ArgType argType;
		const std::string command;
		const enum Type type;
		typedef std::tr1::function<void(const std::string& command, Comment* comment)> Func;
		const Func func;
		Command(const enum ArgType argType, const std::string& command, const enum Type type, Func func)
		:argType(argType), command(command), type(type), func(func){};
		virtual ~Command(){};
		bool execute(const std::string& command, Comment* comment) const;
	} Commands[];
	static const size_t CommandsSize;
public:
	static bool interpret(const std::string& command, Comment* comment);
public:
	enum Device {
		iPhone,
		docomo,
		softbank
	};
	enum Size{
		Big,
		Small,
		Medium
	};
	enum PlaceX{
		Right,
		Left
	};
	enum PlaceY{
		Top,
		Bottom,
		Middle
	};
	DEF_ATTR_ACCESSOR(public, public, const meta::Comment*, orig);
	DEF_ATTR_ACCESSOR(public, public, float, from);
	DEF_ATTR_ACCESSOR(public, public, float, to);
	DEF_ATTR_ACCESSOR(public, public, bool, isButton);
	DEF_ATTR_ACCESSOR(public, public, bool, fromButton);
	DEF_ATTR_ACCESSOR(public, public, bool, full);
	DEF_ATTR_ACCESSOR(public, public, bool, sage);
	DEF_ATTR_ACCESSOR(public, public, bool, patissier);
	DEF_ATTR_ACCESSOR(public, public, enum Device, device);
	DEF_ATTR_ACCESSOR(public, public, bool, vibisle);
	DEF_ATTR_ACCESSOR(public, public, enum Size, size);
	DEF_ATTR_ACCESSOR(public, public, enum PlaceX, placeX);
	DEF_ATTR_ACCESSOR(public, public, enum PlaceY, placeY);
	DEF_ATTR_ACCESSOR(public, public, unsigned int, color);
	DEF_ATTR_ACCESSOR(public, public, unsigned int, shadowColor);
public:
	Comment(const meta::Comment* comment);
	virtual ~Comment();
private:
	void interpret();
public:
public:
	std::tr1::shared_ptr<nekomata::system::Comment> createNekomataComment();
};

}}
#endif /* CONTEXT_COMMENT_H_ */
