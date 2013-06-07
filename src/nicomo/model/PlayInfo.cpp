/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include <fstream>
#include <string>
#include <nicomo/model/PlayInfo.h>
#include <nicomo/model/ReplaceTable.h>

namespace nicomo {
namespace model {

PlayInfo::PlayInfo(cinamo::Logger& log, const std::string& filename)
:replaceTable_(nullptr)
{
	std::ifstream stream(filename.c_str());
	std::string str;
	stream >> str;
	cinamo::FormPayload b;
	b.readURLEncoded(str);

	user_id(b.getLong("user_id"));
	thread(b.getLong("thread_id"));
	is_premium(b.getBool("is_premium"));
	optional_thread(b.optLong("optional_thread_id", -1));
	replaceTable_ = b.has("ng_up") ? new ReplaceTable(b.getString("ng_up")) : 0;
}

PlayInfo::~PlayInfo() {
	if(replaceTable_){
		delete replaceTable_;
	}
}

const ReplaceTable* PlayInfo::replaceTable() const
{
	return replaceTable_;
}

}}
