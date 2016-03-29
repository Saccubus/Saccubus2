/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <string>
#include <cinamo/ClassUtil.h>

namespace nicomo {
namespace model {

/**
 * getflv内で指定される、
 * コメントフィルタ機能の置換テーブルの一つを表現
 * ！！　イミュータブル　！！
 */
class ReplaceItem final{
private:
	DEFINE_MEMBER_CONST(public, std::string, from);
	DEFINE_MEMBER_CONST(public, std::string, to);
	DEFINE_MEMBER_CONST(public, bool, whole);
public:
	ReplaceItem(const std::string& from, const std::string& to, bool whole);
	ReplaceItem(const ReplaceItem& other);
	~ReplaceItem() = default;
public:
	std::string replace(const std::string& target) const;
};

}}
