/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include "../../TestCommon.h"
#include <nicomo/model/Comment.h>

namespace nicomock {
namespace model {

class Comment: public nicomo::model::Comment {
public:
	Comment();
	virtual ~Comment() noexcept = default;
public:
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, unsigned long long, thread);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, unsigned long long, no);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, float, vpos);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, unsigned long long, date);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, unsigned long long, deleted);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, long long, score);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, std::string, user_id);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, std::string, mail);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, std::string, message);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, bool, anonymity);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, bool, leaf);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, bool, premium);
	MOCK_ACCESSOR_EXPAND(nicomo::model::Comment, bool, fork);
};

}}
