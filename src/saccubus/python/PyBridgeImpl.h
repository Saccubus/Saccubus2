/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <Python.h>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cinamo/Logger.h>
#include "../classdefs.h"

namespace saccubus {
namespace python {

class Session;

class PyBridgeImpl {
private:
	cinamo::Logger& log;
public:
	PyBridgeImpl(cinamo::Logger& log);
	virtual ~PyBridgeImpl();
	std::unique_ptr<Session> createSession();
};

class Session {
private:
	cinamo::Logger& log;
private:
	PyObject* global;
	PyObject* local;
private:
	void outException(std::stringstream& msg, PyObject* const type, PyObject* const value, PyObject* const tb);
	void printExceptionLog();
	/**
	 * これらの関数は、新しい参照を返しますし、引数の参照カウントを削ります。
	 */
	PyObject* findMethod(const std::string& module, const std::string& name);
	PyObject* findMethod(const std::string& name);
	PyObject* executeCallable(PyObject* obj, PyObject* argList,PyObject* argDict);
	std::map<std::string, std::string> parseDict(PyObject* dictObj);
	bool parseBool(PyObject* boolObj);
	PyObject* createDict(const std::map<std::string, std::string>& args);
	PyObject* createArgTuple(const std::multimap<std::string, std::string>& args);
	/**
	 * これらの関数は、引数の参照カウントを削りません。
	 */
	std::string toString(PyObject* obj);
	std::string toRepr(PyObject* obj);
public:
	Session(cinamo::Logger& log);
	virtual ~Session();
public:
	void loadFile(const std::string& file);
	std::map<std::string, std::string> executeMethodDict(const std::string& module, const std::string& name, const std::multimap<std::string, std::string>& args);
	std::map<std::string, std::string> executeMethodDict(const std::string& name, const std::multimap<std::string, std::string>& args);
	bool executeMethodBool(const std::string& module, const std::string& name, const std::multimap<std::string, std::string>& args);
	bool executeMethodBool(const std::string& name, const std::multimap<std::string, std::string>& args);
};

}}
