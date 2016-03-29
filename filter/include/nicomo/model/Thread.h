/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <string>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include "Comment.h"

namespace nicomo {
namespace model {

/**
 * XML内でのスレッドを表現するクラス
 * ！！　イミュータブル（変更不可）　！！
 */
class Thread {
	DEFINE_MEMBER(public, private, unsigned long long, thread)
	DEFINE_MEMBER(public, private, unsigned long long, ticket)
	DEFINE_MEMBER(public, private, unsigned long long, server_time)
	std::vector<const Comment*> chatList;
public:
	typedef std::vector<const Comment*>::const_iterator Iterator;
	Thread(cinamo::Logger& log, tinyxml2::XMLElement* node);
	Thread(cinamo::Logger& log, tinyxml2::XMLDocument* doc);
	Thread(cinamo::Logger& log, const std::string& filename);
	virtual ~Thread();
private:
	void read(cinamo::Logger& log, tinyxml2::XMLElement* elm);
public:
	Iterator begin() const;
	Iterator end() const;
	size_t size() const;
};

}}
