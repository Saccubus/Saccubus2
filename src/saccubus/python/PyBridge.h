/*
 * PyBridge.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef PYBRIDGE_H_
#define PYBRIDGE_H_

#include <string>
#include <map>
#include <vector>
#include "../classdefs.h"

namespace saccubus {
namespace python {

class PyBridgeImpl;
class PyBridge {
private:
	logging::Logger& log;
	PyBridgeImpl* const impl;
public:
	PyBridge(logging::Logger& log);
	virtual ~PyBridge();
public:
	const meta::Video* resolveResource(const std::string& video_id, const std::vector<std::pair<std::string, std::string> >& args);
	bool askCommentShouldBeIgnored(const char* filename, const meta::Comment& com);
};

}}
#endif /* PYBRIDGE_H_ */
