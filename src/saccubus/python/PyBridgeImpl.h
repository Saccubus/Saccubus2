/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PYBRIDGEIMPL_H_
#define PYBRIDGEIMPL_H_

#include <Python.h>
#include <string>
#include <auto_ptr.h>
#include <map>
#include <vector>
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
	PyObject* executeCallable(PyObject* obj, PyObject* argList,PyObject* argDict);
	std::map<std::string, std::string> parseDict(PyObject* dictObj);
	bool parseBool(PyObject* boolObj);
	PyObject* createDict(const std::map<std::string, std::string>& args);
	PyObject* createArgTuple(const std::vector<std::pair<std::string, std::string> >& args);
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
	std::map<std::string, std::string> executeMethodDict(const std::string& module, const std::string& name, const std::vector<std::pair<std::string, std::string> >& args);
	std::map<std::string, std::string> executeMethodDict(const std::string& name, const std::vector<std::pair<std::string, std::string> >& args);
	bool executeMethodBool(const std::string& module, const std::string& name, const std::vector<std::pair<std::string, std::string> >& args);
	bool executeMethodBool(const std::string& name, const std::vector<std::pair<std::string, std::string> >& args);
};

}}
#endif /* PYBRIDGEIMPL_H_ */
