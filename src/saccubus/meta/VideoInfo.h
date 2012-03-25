/*
 * VideoInfo.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef VIDEOINFO_H_
#define VIDEOINFO_H_

#include "../util/Bundle.h"
#include "ReplaceTable.h"

namespace saccubus {
namespace meta {

class VideoInfo {
private:
	const util::Bundle bundle;
	const ReplaceTable replaceTable_;
public:
	VideoInfo(const std::string& info);
	virtual ~VideoInfo();
public:
	const ReplaceTable& replaceTable() const;
};

}}
#endif /* VIDEOINFO_H_ */
