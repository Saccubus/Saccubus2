/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <map>
#include <sstream>

#include <cinamo/String.h>

#include <nicomo/model/Video.h>
#include <nicomo/model/Comment.h>

#include "PyBridge.h"
#include "PyBridgeImpl.h"
#include "ScriptException.h"

namespace saccubus {
namespace python {

PyBridge::PyBridge(cinamo::Logger& log)
:log(log)
,impl(new PyBridgeImpl(log))
{
}

const nicomo::model::Video* PyBridge::resolveResource(const std::string& video_id, const std::multimap<std::string, std::string>& args)
{
	using nicomo::model::Video;
	std::unique_ptr<Session> session = impl->createSession();
	std::multimap<std::string, std::string> callArgs(args.begin(), args.end());
	callArgs.insert(std::pair<std::string, std::string>("video-id", video_id));
	std::map<std::string, std::string> res = session->executeMethodDict("saccubus.resource.resolve", "fromNative", callArgs);
	std::map<std::string, std::string>::const_iterator end = res.end();
	Video* ctx = new Video(this->log);
	if(res.find("video") == end){
		throw ScriptException(__FILE__, __LINE__, "Resolve failed. There is no videofile.");
	}
	ctx->initVideoFile(res.find("video")->second);
	std::vector<std::string> threads;
	if(res.find("thread") != end){
		threads = cinamo::splitLine(res.find("thread")->second);
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

bool PyBridge::askCommentShouldBeIgnored(const std::string& filename, const nicomo::model::Comment& com)
{
	if(!(&filename) || filename.size() <= 0){
		return false;
	}
	std::unique_ptr<Session> session = impl->createSession();
	session->loadFile(filename);
	std::multimap<std::string, std::string> callArgs;
	callArgs.insert(std::pair<std::string, std::string>("thread", cinamo::format("%llu", com.thread()).c_str()));
	callArgs.insert(std::pair<std::string, std::string>("no", cinamo::format("%llu", com.no()).c_str()));
	callArgs.insert(std::pair<std::string, std::string>("vpos", cinamo::format("%f", com.vpos()).c_str()));
	callArgs.insert(std::pair<std::string, std::string>("date", cinamo::format("%llu", com.date()).c_str()));
	callArgs.insert(std::pair<std::string, std::string>("deleted", cinamo::format("%llu", com.deleted()).c_str()));
	callArgs.insert(std::pair<std::string, std::string>("score", cinamo::format("%lld", com.score()).c_str()));
	callArgs.insert(std::pair<std::string, std::string>("user_id", com.user_id().c_str()));
	callArgs.insert(std::pair<std::string, std::string>("mail", com.mail().c_str()));
	callArgs.insert(std::pair<std::string, std::string>("message", com.message().c_str()));
	callArgs.insert(std::pair<std::string, std::string>("anonymity", com.anonymity() ? "true" : "false"));
	callArgs.insert(std::pair<std::string, std::string>("leaf", com.leaf() ? "true" : "false"));
	callArgs.insert(std::pair<std::string, std::string>("premium", com.premium() ? "true" : "false"));
	callArgs.insert(std::pair<std::string, std::string>("fork", com.fork() ? "true" : "false"));
	return session->executeMethodBool("shouldCommentBeIgnored", callArgs);
}


PyBridge::~PyBridge() {
	delete impl;
}

}}
