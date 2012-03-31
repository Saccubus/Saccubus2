/*
 * PyBridgeImpl.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef PYBRIDGEIMPL_H_
#define PYBRIDGEIMPL_H_

#include <Python.h>
#include <string>
#include <auto_ptr.h>
#include <map>
#include "../classdefs.h"

namespace saccubus {
namespace python {

class Session;

class PyBridgeImpl {
private:
	logging::Logger& log;
public:
	PyBridgeImpl(logging::Logger& log);
	virtual ~PyBridgeImpl();
	std::auto_ptr<Session> createSession();
};

class Session {
private:
	logging::Logger& log;
private:
	PyObject* global;
	PyObject* local;
public:
	Session(logging::Logger& log);
	virtual ~Session();
public:
	void loadFile(const std::string& file);
	std::map<std::string, std::string> executeMethod(const std::string& module, const std::string& name, const std::map<std::string, std::string>& args);
};

}}
#endif /* PYBRIDGEIMPL_H_ */
