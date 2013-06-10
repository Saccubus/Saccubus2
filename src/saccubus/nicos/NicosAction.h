/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <vector>
#include <cinamo/ClassUtil.h>
#include <nicomo/model/Comment.h>
#include "../layer/item/Comment.h"

namespace saccubus {
namespace nicos {

std::string escape(const std::string& str);
std::string escape(bool val);
std::string escape(int val);
std::string escape(float val);

class NicosAction {
	DISABLE_COPY_AND_ASSIGN(NicosAction);
	DEFINE_MEMBER_REF(public, layer::item::Comment const, com)
private:
	std::size_t msgIndex_;
	std::vector<std::string> msgTokens_;
	std::vector<std::string> mailTokens_;
	std::string nextToken(bool require);
public:
	NicosAction(layer::item::Comment const& com, const std::vector<std::string>& tokens);
	virtual ~NicosAction() = 0;
public:
	std::string trans();
protected:
	virtual void read() = 0;
	virtual std::string write() = 0;
public:
	std::string commail(bool require=false);
	std::string string(bool require=false);
	bool visilibity(bool require=false);
	int times(bool require=false);
	bool hasMail(std::string const& token) const;
};

}}
