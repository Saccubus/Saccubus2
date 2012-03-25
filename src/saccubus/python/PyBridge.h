/*
 * PyBridge.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef PYBRIDGE_H_
#define PYBRIDGE_H_

namespace saccubus {
namespace python {

class PyBridgeImpl;
class PyBridge {
private:
	PyBridgeImpl* const impl;
public:
	PyBridge();
	virtual ~PyBridge();
};

}}
#endif /* PYBRIDGE_H_ */
