/*
 * PlayInfo.h
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#ifndef PLAYINFO_H_
#define PLAYINFO_H_

#include "../util/ClassAccessor.h"
#include "../util/Bundle.h"
#include "ReplaceTable.h"

namespace saccubus {
namespace meta {

/**
 * getflv内で指定される、
 * 動画の情報を表現するクラス
 * ！！　イミュータブル　！！
 */
class PlayInfo {
private:
	const util::Bundle bundle;
	const ReplaceTable _replaceTable;
	DEF_ATTR_ACCESSOR(public, private, long long, user_id);
	DEF_ATTR_ACCESSOR(public, private, bool, is_premium);
	DEF_ATTR_ACCESSOR(public, private, long long, thread);
public:
	PlayInfo(const std::string& info);
	virtual ~PlayInfo();
public:
	const ReplaceTable& replaceTable() const;
};

}}
#endif /* PLAYINFO_H_ */
