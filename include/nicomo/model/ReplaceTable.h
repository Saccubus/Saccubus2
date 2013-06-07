/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <vector>
#include <string>
#include "./ReplaceItem.h"

namespace nicomo {
namespace model {
/**
 * getflv内で指定される、
 * コメントフィルタ機能の置換テーブル全体を表現
 * ！！　イミュータブル　！！
 */
class ReplaceTable {
private:
	std::vector<const ReplaceItem*> replaceList;
public:
	ReplaceTable(const std::string& entry);
	virtual ~ReplaceTable();
public:
	std::string replace(const std::string& target) const;
};

}}
