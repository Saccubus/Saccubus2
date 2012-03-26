/*
 * ReplaceItem.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef REPLACEITEM_H_
#define REPLACEITEM_H_

#include <string>

namespace saccubus {
namespace meta {

/**
 * getflv内で指定される、
 * コメントフィルタ機能の置換テーブルの一つを表現
 * ！！　イミュータブル　！！
 */
class ReplaceItem {
private:
	const std::string from_;
	const std::string to_;
	bool whole_;
public:
	ReplaceItem(const std::string& from, const std::string& to, bool whole);
	ReplaceItem(const ReplaceItem& other);
	virtual ~ReplaceItem();
public:
	std::string from() const;
	std::string to() const;
	bool whole() const;
public:
	std::string replace(const std::string& target) const;
};

}}
#endif /* REPLACEITEM_H_ */
