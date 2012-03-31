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
private:
	void outException(std::stringstream& msg, PyObject* v);
	void printExceptionLog();
	/**
	 * これらの関数は、新しい参照を返しますし、引数の参照カウントを削ります。
	 */
	PyObject* findMethod(const std::string& module, const std::string& name);
	PyObject* findMethod(const std::string& name);
	PyObject* executeCallable(PyObject* obj, PyObject* argDict);
	std::map<std::string, std::string> parseDict(PyObject* dictObj);
	bool parseBool(PyObject* boolObj);
	PyObject* createDict(const std::map<std::string, std::string>& args);
	/**
	 * これらの関数は、引数の参照カウントを削りません。
	 */
	std::string toString(PyObject* obj);
	std::string toRepr(PyObject* obj);
public:
	Session(logging::Logger& log);
	virtual ~Session();
public:
	void loadFile(const std::string& file);
	std::map<std::string, std::string> executeMethodDict(const std::string& module, const std::string& name, const std::map<std::string, std::string>& args);
	std::map<std::string, std::string> executeMethodDict(const std::string& name, const std::map<std::string, std::string>& args);
	bool executeMethodBool(const std::string& module, const std::string& name, const std::map<std::string, std::string>& args);
	bool executeMethodBool(const std::string& name, const std::map<std::string, std::string>& args);
};

}}
#endif /* PYBRIDGEIMPL_H_ */
