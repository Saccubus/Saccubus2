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

#include <string>
#include <fstream>
#include <sstream>

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
/**
 * ファイルを読んで実行します。
 * ユーザースクリプトの読み込みなどに。
 * （さきゅばす本体はパスに入っているので、これを使わなくても読み込めます）
 */
void Session::loadFile(const std::string& file)
{
	std::ifstream stream(file.c_str());
	//ファイルのオープン
	if(!stream){
		log.e(TAG, "File \"%s\" not found.", file.c_str());
		throw ScriptException("File \"%s\" not found.", file.c_str());
	}
	//ファイルの読み込み
	stream.seekg(0, std::istream::beg);
	const std::istream::pos_type first = stream.tellg();
	stream.seekg(0, std::istream::end);
	const std::istream::pos_type end = stream.tellg();
	stream.seekg(0, std::istream::beg);
	const std::streamsize len = end-first;
	std::streamsize pos = 0;
	std::auto_ptr<char> buffer(new char[len+1]);
	if(!buffer.get()){
		log.e(TAG, "Failed to allocate memory for \"%s\"", file.c_str());
		throw ScriptException("Failed to allocate memory for \"%s\"", file.c_str());
	}

	while(stream && pos < len){
		stream.read(buffer.get()+pos, len);
		pos += stream.gcount();
	}
	if(len != pos){
		log.e(TAG, "Failed to read \"%s\".", file.c_str());
		throw ScriptException("Failed to read \"%s\".", file.c_str());
	}
	buffer.get()[len]='\0';

	//コードのコンパイル
	PyObject* code = Py_CompileString(buffer.get(), file.c_str(), Py_file_input);
	if(!code){
		log.e(TAG, "Failed to compile: %s", file.c_str());
		this->printExceptionLog();
		throw ScriptException("Failed to run: %s", file.c_str());
	}
	//実行
	PyObject* res = PyEval_EvalCode(code, this->global, this->local);
	Py_DECREF(code);
	if(!res){
		log.e(TAG, "Failed to run: %s", file.c_str());
		this->printExceptionLog();
		throw ScriptException("Failed to run: %s", file.c_str());
	}
}

/**
 *
 */
void Session::outException(std::stringstream& msg, PyObject* v){
	if(!v){
		return;
	}
	Py_INCREF(v);
	if(!PyExceptionInstance_Check(v)){
		log.e(TAG, "TypeError: outException: Exception expected for value, %s found.", Py_TYPE(v)->tp_name);
	}
	PyObject* cause = PyException_GetCause(v);
	if(cause){
		outException(msg, cause);
	}
	PyObject* type = (PyObject*)Py_TYPE(v);

	//FIXME: うまく出力できないことがある
	msg << "File \"" << toString(PyObject_GetAttrString(v, "filename")) << "\", line " << toString(PyObject_GetAttrString(v, "lineno")) << ", in " << toString(PyObject_GetAttrString(type, "__module__")) << std::endl;
	msg << PyExceptionClass_Name(type) << ": " << toString(v) << std::endl;
	msg << "here: " << toString(PyObject_GetAttrString(v, "text")) << std::endl;
	Py_DECREF(v);
}
void Session::printExceptionLog()
{
	std::stringstream msg;
	PyObject *exception, *v, *tb;
	PyErr_Fetch(&exception, &v, &tb);
	PyErr_NormalizeException(&exception, &v, &tb);
	msg << "Python says: \n";
	outException(msg, v);
	log.e(TAG, msg.str());
}

/**
 * from {module} import {name}して、その{name}の関数ポインタを返します。
 */
PyObject* Session::findMethod(const std::string& module, const std::string& name)
{
	PyObject* imported = 0;
	{
		PyObject* const impList = PyList_New(1);
		PyObject* const impName = PyUnicode_DecodeUTF8(name.c_str(), name.size(), "ignore");
		PyList_Append(impList, impName);
		imported = PyImport_ImportModuleEx(const_cast<char*>(module.c_str()), this->global, this->local, impList);
		Py_DecRef(impName);
		Py_DecRef(impList);
	}

	if(!imported){
		log.e(TAG, "'%s.%s' is not found!", module.c_str(), name.c_str());
		throw ScriptException("'%s.%s' is not found!", module.c_str(), name.c_str());
	}else{
		if(log.t()) log.t(TAG, "Module for \"%s\" imported: '%s'", name.c_str(), toRepr(imported).c_str());
	}

	PyObject* func = PyDict_GetItemString(PyModule_GetDict(imported), name.c_str());
	if(!func){
		log.e(TAG, "\"%s.%s\" is not found!", module.c_str(), name.c_str());
		throw ScriptException("\"%s.%s\" is not found!", module.c_str(), name.c_str());
	}
	std::string repr = toRepr(func).c_str();
	if(!PyCallable_Check(func)){
		this->printExceptionLog();
		log.e(TAG, "\"%s.%s\" is not callable! It's '%s'", module.c_str(), name.c_str(), repr.c_str());
		throw ScriptException("\"%s.%s\" is not callable! It's '%s'", module.c_str(), name.c_str(), repr.c_str());
	}
	Py_XINCREF(func);
	Py_XDECREF(imported);imported = 0;
	return func;

}
/**
 * import済みのシンボルを返します。
 * ユーザースクリプトや、ビルトイン関数用。
 */
PyObject* Session::findMethod(const std::string& name)
{
	PyObject* func = PyDict_GetItemString(this->local, name.c_str());
	if(!func){
		log.e(TAG, "\"%s\" is not found!", name.c_str());
		throw ScriptException("\"%s\" is not found!", name.c_str());
	}
	std::string repr = toRepr(func).c_str();
	if(!PyCallable_Check(func)){
		this->printExceptionLog();
		log.e(TAG, "\"%s\" is not callable! It's '%s'", name.c_str(), repr.c_str());
		throw ScriptException("\"%s\" is not callable! It's '%s'", name.c_str(), repr.c_str());
	}else{
		if(log.t()) log.t(TAG, "\"%s\" found: %s", name.c_str(), repr.c_str());
	}
	Py_XINCREF(func);
	return func;
}

/**
 * dictObjectを、mapに変換する
 */
std::map<std::string, std::string> Session::parseDict(PyObject* dictObj)
{
	std::map<std::string, std::string> map;
	if(!PyDict_Check(dictObj)){
		log.w(TAG, "The object is not a dictionary. It's '%s'", toRepr(dictObj).c_str());
		return map;
	}
	PyObject* keys = PyDict_Keys(dictObj);
	const size_t max =PyList_Size(keys);
	for(size_t i=0;i<max;++i){
		PyObject* keyObj = PyList_GetItem(keys, i);
		std::string key = toString(keyObj);
		PyObject* valObj = PyDict_GetItem(dictObj, keyObj);
		std::string val = toString(valObj);
		map.insert(std::pair<std::string, std::string>(key, val));
	}
	Py_DECREF(keys);
	Py_DECREF(dictObj);
	return map;
}

bool Session::parseBool(PyObject* boolObj)
{
	if(!PyBool_Check(boolObj)){
		log.w(TAG, "The object is not a bool object. It's '%s'", toRepr(boolObj).c_str());
		return false;
	}
	bool result = Py_True == boolObj;
	Py_DECREF(boolObj);
	return result;
}

/**
 * std::vector<std::pair<std::string, std::string> >から、引数用のタプルのタプルを作成します。
 */
PyObject* Session::createArgTuple(const std::vector<std::pair<std::string, std::string> >& args)
{
	PyObject* const argObj = PyTuple_New(args.size());
	int i=0;
	for(std::vector<std::pair<std::string, std::string> >::const_iterator it = args.begin(); it != args.end();++it)
	{
		PyObject* tuple = PyTuple_New(2);
		PyObject* key = PyUnicode_DecodeUTF8(it->first.c_str(), it->first.size(), "ignore");
		PyObject* val = PyUnicode_DecodeUTF8(it->second.c_str(), it->second.size(), "ignore");
		PyTuple_SetItem(tuple, 0, key);
		PyTuple_SetItem(tuple, 1, val);
		PyTuple_SetItem(argObj, i++, tuple);
	}
	return argObj;
}
/**
 * str(obj)の結果を返す。
 */
std::string Session::toString(PyObject* obj)
{
	PyObject* const val_o = PyObject_Str(obj);
	PyObject* const val_s = PyUnicode_AsUTF8String(val_o);
	std::string val(PyBytes_AsString(val_s));
	Py_XDECREF(val_s);
	Py_XDECREF(val_o);
	return val;
}
/**
 * repr(obj)の結果を返す。
 */
std::string Session::toRepr(PyObject* obj)
{
	PyObject* const repr_o = PyObject_Repr(obj);
	PyObject* const repr = PyUnicode_AsUTF8String(repr_o);
	std::string val(PyBytes_AsString(repr));
	Py_XDECREF(repr);
	Py_XDECREF(repr_o);
	return val;

}

/**
 * obj(*dict)を実行して結果を返します
 */
PyObject* Session::executeCallable(PyObject* obj, PyObject* argTuple,PyObject* argDict)
{
	PyObject* res = 0;
	{
		if(!argTuple){
			argTuple = PyTuple_New(0);
		}
		if(!argDict){
			argDict = PyDict_New();
		}
		res = PyObject_Call(obj, argTuple, argDict);
		Py_DECREF(argTuple);
		Py_DECREF(argDict);
		Py_DECREF(obj);
	}
	if(!res){
		this->printExceptionLog();
		log.e(TAG, "Failed to run: %s", toRepr(obj).c_str());
		throw ScriptException("Failed to run: %s", toRepr(obj).c_str());
	}
	return res;
}

std::map<std::string, std::string> Session::executeMethodDict(const std::string& module, const std::string& name, const std::vector<std::pair<std::string, std::string> >& args)
{
	return parseDict(executeCallable(findMethod(module, name), createArgTuple(args), 0));
}

std::map<std::string, std::string> Session::executeMethodDict(const std::string& name, const std::vector<std::pair<std::string, std::string> >& args)
{
	return parseDict(executeCallable(findMethod(name), createArgTuple(args), 0));
}
bool Session::executeMethodBool(const std::string& module, const std::string& name, const std::vector<std::pair<std::string, std::string> >& args)
{
	return parseBool(executeCallable(findMethod(module, name), createArgTuple(args), 0));
}
bool Session::executeMethodBool(const std::string& name, const std::vector<std::pair<std::string, std::string> >& args)
{
	return parseBool(executeCallable(findMethod(name), createArgTuple(args), 0));
}

Session::~Session(){
	Py_DECREF(this->local);
	this->global = 0;
	this->local = 0;
}

}}
