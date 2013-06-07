/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <vector>
#include <cinamo/ClassUtil.h>
#include <nicomo/model/Comment.h>

namespace nekomata {
namespace trans {

std::string escape(const std::string& str);
std::string escape(bool val);

class NicosAction {
	DISABLE_COPY_AND_ASSIGN(NicosAction);
	DEFINE_MEMBER_REF(public, nicomo::model::Comment const, com)
private:
	std::size_t msgIndex;
	std::vector<std::string> msgTokens;
	std::string nextToken(bool require);
public:
	NicosAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens);
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
};

}}
