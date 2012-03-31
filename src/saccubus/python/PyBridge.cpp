/*
 * PyBridge.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "PyBridge.h"
#include "PyBridgeImpl.h"

namespace saccubus {
namespace python {

PyBridge::PyBridge(logging::Logger& log)
:log(log)
,impl(new PyBridgeImpl(log))
{
	// TODO Auto-generated constructor stub

}

PyBridge::~PyBridge() {
	delete impl;
}

}}
