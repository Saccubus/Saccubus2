/*
 * MetaInfo.h
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#ifndef METAINFO_H_
#define METAINFO_H_

#include "../classdefs.h"
#include "../util/ClassAccessor.h"
#include "ReplaceTable.h"
#include <string>
#include <libxml2/libxml/tree.h>

namespace saccubus {
namespace meta {

class MetaInfo{
	DEF_ATTR_ACCESSOR(public, private, std::string, title);
public:
	MetaInfo(logging::Logger& log, xmlNode* node);
	MetaInfo(logging::Logger& log, xmlDoc* doc);
	MetaInfo(logging::Logger& log, const std::string& filename);
	virtual ~MetaInfo();
private:
	void read(logging::Logger& log, xmlNode* node);
};

}}
#endif /* METAINFO_H_ */
