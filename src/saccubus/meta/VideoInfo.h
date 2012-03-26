/*
 * VideoInfo.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef VIDEOINFO_H_
#define VIDEOINFO_H_

#include "../util/Bundle.h"
#include "../util/ClassAccessor.h"
#include "ReplaceTable.h"

namespace saccubus {
namespace meta {

/**
 * getflv内で指定される、
 * 動画の情報を表現するクラス
 * ！！　イミュータブル　！！
 */
class VideoInfo {
private:
	const util::Bundle bundle;
	const ReplaceTable replaceTable_;
	DEF_ATTR_ACCESSOR(public, private, long long, user_id);
	DEF_ATTR_ACCESSOR(public, private, bool, is_premium);
	DEF_ATTR_ACCESSOR(public, private, long long, thread);
public:
	VideoInfo(const std::string& info);
	virtual ~VideoInfo();
public:
	const ReplaceTable& replaceTable() const;
};

}}
#endif /* VIDEOINFO_H_ */
