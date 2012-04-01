/*
 * PyBridge.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include <map>
#include "PyBridge.h"
#include "PyBridgeImpl.h"

namespace saccubus {
namespace python {

PyBridge::PyBridge(logging::Logger& log)
:log(log)
,impl(new PyBridgeImpl(log))
{
}

std::map<std::string, std::string> PyBridge::resolveResource(const std::string& video_id, const std::vector<std::pair<std::string, std::string> >& args)
{
	std::auto_ptr<Session> session = impl->createSession();
	std::vector<std::pair<std::string, std::string> > callArgs(args.begin(), args.end());
	callArgs.push_back(std::pair<std::string, std::string>("video-id", video_id));
	return session->executeMethodDict("saccubus.resource.resolve", "fromNative", callArgs);
}

PyBridge::~PyBridge() {
	delete impl;
}

}}
