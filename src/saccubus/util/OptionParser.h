/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#pragma once
#include <vector>
#include <string>
#include <cinamo/ClassUtil.h>

/**
 * FIXME: これはひどい車輪の再発明
 */

namespace saccubus {
namespace util {

class Option {
public:
	enum Type {
		Normal,
		Prefix
	};
	enum Argument{
		No,
		Require,
		Optional
	};
	DEFINE_MEMBER(public, private, std::string, name);
	DEFINE_MEMBER(public, private, enum Type, type);
	DEFINE_MEMBER(public, private, enum Argument, argument);
protected:
	Option(std::string const& name, enum Type t, enum Argument a);
public:
	virtual ~Option();
public:
	virtual void invoke(const std::string& name, const std::string* arg) = 0;
};

class OptionParser {
	std::vector<Option*> opts;
public:
	OptionParser();
	virtual ~OptionParser();
public:
	void add(Option* opt);
	void parse(int argc, char** argv, std::vector<std::string>& left);
};

}}
