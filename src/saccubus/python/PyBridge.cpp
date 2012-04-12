/*
 * PyBridge.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include <map>
#include <sstream>
#include "../meta/Video.h"
#include "PyBridge.h"
#include "PyBridgeImpl.h"
#include "ScriptException.h"
#include "../meta/Comment.h"
#include "../util/StringUtil.h"

namespace saccubus {
namespace python {

PyBridge::PyBridge(logging::Logger& log)
:log(log)
,impl(new PyBridgeImpl(log))
{
}

const meta::Video* PyBridge::resolveResource(const std::string& video_id, const std::vector<std::pair<std::string, std::string> >& args)
{
	std::auto_ptr<Session> session = impl->createSession();
	std::vector<std::pair<std::string, std::string> > callArgs(args.begin(), args.end());
	callArgs.push_back(std::pair<std::string, std::string>("video-id", video_id));
	std::map<std::string, std::string> res = session->executeMethodDict("saccubus.resource.resolve", "fromNative", callArgs);
	std::map<std::string, std::string>::const_iterator end = res.end();
	meta::Video* ctx = new meta::Video(this->log);
	if(res.find("video") == end){
		throw ScriptException("Resolve failed. There is no videofile.");
	}
	ctx->initVideoFile(res.find("video")->second);
	std::vector<std::string> threads;
	if(res.find("thread") != end){
		std::istringstream ss(res.find("thread")->second);
		std::string str;
		while(std::getline(ss, str, '\n')){
			threads.push_back(str);
		}
	}
	ctx->initThread(threads);
	if(res.find("meta_info") != end){
		ctx->initMetaInfo(res.find("meta_info")->second);
	}
	if(res.find("play_info") != end){
		ctx->initPlayInfo(res.find("play_info")->second);
	}
	return ctx;
}

bool PyBridge::askCommentShouldBeIgnored(const char* filename, const meta::Comment& com)
{
	if(!filename){
		return false;
	}
	std::auto_ptr<Session> session = impl->createSession();
	session->loadFile(filename);
	std::vector<std::pair<std::string, std::string> > callArgs;
	callArgs.push_back(std::pair<std::string, std::string>("thread", util::format("%llu", com.thread()).c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("no", util::format("%llu", com.no()).c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("vpos", util::format("%f", com.vpos()).c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("date", util::format("%llu", com.date()).c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("deleted", util::format("%llu", com.deleted()).c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("score", util::format("%lld", com.score()).c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("user_id", com.user_id().c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("mail", com.mail().c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("message", com.message().c_str()));
	callArgs.push_back(std::pair<std::string, std::string>("anonymity", com.anonymity() ? "true" : "false"));
	callArgs.push_back(std::pair<std::string, std::string>("leaf", com.leaf() ? "true" : "false"));
	callArgs.push_back(std::pair<std::string, std::string>("premium", com.premium() ? "true" : "false"));
	callArgs.push_back(std::pair<std::string, std::string>("fork", com.fork() ? "true" : "false"));
	return session->executeMethodBool("shouldCommentBeIgnored", callArgs);
}


PyBridge::~PyBridge() {
	delete impl;
}

}}
