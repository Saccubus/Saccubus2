/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <memory>
#include <string>
#include <vector>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include <tinyxml2.h>

namespace nicomo {
namespace model {

/**
 * XML内のコメントを表現するクラス。
 * ！！　イミュータブル（変更不可）　！！
 */
class Comment{
	DEFINE_MEMBER(public, protected, unsigned long long, thread)
	DEFINE_MEMBER(public, protected, unsigned long long, no)
	DEFINE_MEMBER(public, protected, float, vpos)
	DEFINE_MEMBER(public, protected, unsigned long long, date)
	DEFINE_MEMBER(public, protected, unsigned long long, deleted)
	DEFINE_MEMBER(public, protected, long long, score)
	DEFINE_MEMBER(public, protected, std::string, user_id)
	DEFINE_MEMBER(public, protected, std::string, message)
	DEFINE_MEMBER(public, protected, std::string, mail)
	DEFINE_MEMBER(public, protected, bool, anonymity)
	DEFINE_MEMBER(public, protected, bool, leaf)
	DEFINE_MEMBER(public, protected, bool, premium)
	DEFINE_MEMBER(public, protected, bool, fork)
protected:
	Comment();
public:
	Comment(cinamo::Logger& log, tinyxml2::XMLElement* const elem);
	virtual ~Comment() noexcept = default;
public:
	struct CompareLessByVpos
	{
		bool operator() (const Comment* a, const Comment* b)
		{
			return a->vpos() < b->vpos();
		}
		bool operator() (const float& a, const Comment* b)
		{
			return a < b->vpos();
		}
		bool operator() (const Comment* a, const float& b)
		{
			return a->vpos() < b;
		}
	};
};

}}
