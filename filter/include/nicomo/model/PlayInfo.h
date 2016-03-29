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
#include <cinamo/FormPayload.h>
#include <nicomo/Model.h>

namespace nicomo {
namespace model {

using namespace nicomo::model;

/**
 * getflv内で指定される、
 * 動画の情報を表現するクラス
 * ！！　イミュータブル　！！
 */
class PlayInfo final{
private:
	const ReplaceTable* replaceTable_;
	DEFINE_MEMBER(public, private, long long, user_id);
	DEFINE_MEMBER(public, private, bool, is_premium);
	DEFINE_MEMBER(public, private, long long, thread);
	DEFINE_MEMBER(public, private, long long, optional_thread);
public:
	PlayInfo(cinamo::Logger& log, const std::string& filename);
	~PlayInfo();
public:
	const ReplaceTable* replaceTable() const;
};

}}
