/*
 * PyBridgeImpl.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include <string>

#include "../logging/Exception.h"
#include "../logging/Logger.h"
#include "./ScriptException.h"

#include "PyBridgeImpl.h"
namespace saccubus {
namespace python {

static const std::string TAG("PyBridgeImpl");

PyBridgeImpl::PyBridgeImpl(logging::Logger& log)
:log(log)
{
	Py_Initialize();
	if(!Py_IsInitialized()){
		throw logging::Exception("Failed to init Python!!");
	}
	Session session(log);
}
std::auto_ptr<Session> PyBridgeImpl::createSession()
{
	std::auto_ptr<Session> session(new Session(this->log));

	return session;
}
PyBridgeImpl::~PyBridgeImpl() {
	Py_Finalize();
}

Session::Session(logging::Logger& log)
:log(log)
{
	PyObject* module = PyImport_AddModule("__main__");
	this->global = PyModule_GetDict(module);
	this->local = PyDict_New();
}
void Session::loadFile(const std::string& file)
{
	FILE* f = fopen(file.c_str(), "rb");
	if(!f){
		log.e(TAG, "Failed to open: %s", file.c_str());
		throw ScriptException("Failed to open: %s", file.c_str());
	}
	PyObject* res = PyRun_FileExFlags(f, file.c_str(), Py_file_input, this->global, this->local, 1, 0);
	if(!res){
		log.e(TAG, "Failed to run: %s", file.c_str());
		throw ScriptException("Failed to run: %s", file.c_str());
	}
}

std::map<std::string, std::string> Session::executeMethod(const std::string& module, const std::string& name, const std::map<std::string, std::string>& args)
{
	std::map<std::string, std::string> map;
	// FIXME: グローバル名前空間を使ってしまうのはあまり嬉しくない
	PyObject* imported = PyImport_ImportModule(module.c_str());
	if(!imported){
		log.e(TAG, "Module '%s' is not found!", module.c_str());
		throw ScriptException("Module '%s' not found!", module.c_str());
	}
	PyObject* repr = PyUnicode_AsUTF8String(PyObject_Repr(imported));
	const char* b = PyBytes_AsString(repr);
	log.t(TAG, "Module for \"%s\" imported: %s", name.c_str(), b);
	Py_XDECREF(repr);

	PyObject* func = PyDict_GetItemString(PyModule_GetDict(imported), name.c_str());

	if(!PyCallable_Check(func)){
		PyErr_Print();
		log.e(TAG, "\"%s\" is not callable!", name.c_str());
	}

	PyObject* argsObj = PyTuple_New(0);
	PyObject* dictObj = PyDict_New();
	PyObject* res = PyObject_Call(func, argsObj, dictObj);
	if(!res){
		PyErr_Print();
		log.e(TAG, "Failed to run: %s", name.c_str());
		throw ScriptException("Failed to run: %s", name.c_str());
	}
	if(!PyDict_Check(res)){
		log.w(TAG, "Result of Function \"%s.%s\" is not a dict.", name.c_str());
	}
	Py_XDECREF(imported);imported = 0;
	return map;
}

Session::~Session(){
	Py_DECREF(this->local);
	this->global = 0;
	this->local = 0;
}

}}
