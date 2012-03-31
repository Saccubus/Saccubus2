/*
 * PyBridge.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef PYBRIDGE_H_
#define PYBRIDGE_H_

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
};

}}
#endif /* PYBRIDGE_H_ */
