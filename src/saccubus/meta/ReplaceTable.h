/*
 * ReplaceTable.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef REPLACETABLE_H_
#define REPLACETABLE_H_

#include <vector>
#include <string>
#include "./ReplaceItem.h"

namespace saccubus {
namespace meta {

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
#endif /* REPLACETABLE_H_ */
