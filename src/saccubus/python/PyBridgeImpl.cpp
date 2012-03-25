/*
 * PyBridgeImpl.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../logging/Exception.h"
#include "PyBridgeImpl.h"

namespace saccubus {
namespace python {

PyBridgeImpl::PyBridgeImpl() {
	Py_Initialize();
	if(!Py_IsInitialized()){
		throw logging::Exception("Failed to init Python!!");
	}
}

PyBridgeImpl::~PyBridgeImpl() {
	Py_Finalize();
}
}}
