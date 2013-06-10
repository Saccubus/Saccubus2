/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <sstream>
#include <memory>

#include <cinamo/String.h>
#include <cinamo/XMLAttrParser.h>

#include <nekomata/parser/Parser.h>
#include <nicomo/model/Comment.h>

namespace nicomo {
namespace model {

static std::string TAG("Comment");

Comment::Comment(cinamo::Logger& log, tinyxml2::XMLElement* const elem)
:thread_(0LLU)
,no_(0LLU)
,vpos_(-1)
,date_(0LLU)
,deleted_(0LLU)
,score_(0)
,user_id_("")
,message_("")
,mail_("")
,anonymity_(false)
,leaf_(false)
,premium_(false)
,fork_(false)
{
	cinamo::xml::parseAttr("thread", this->thread_, (unsigned long long)0, elem);
	cinamo::xml::parseAttr("no", this->no_, (unsigned long long)0, elem);
	cinamo::xml::parseAttr("vpos",this->vpos_, (float)0/100, elem);
	this->vpos_ /= 100.0f;
	cinamo::xml::parseAttr("date",this->date_, (unsigned long long)0, elem);
	cinamo::xml::parseAttr("deleted",this->deleted_, (unsigned long long)0, elem);
	cinamo::xml::parseAttr("score",this->score_, (long long)0, elem);
	cinamo::xml::parseAttr("user_id",this->user_id_, std::string(""), elem);
#define PARSE_BOOL_INT(NAME, TO) do{\
		int anon;\
		cinamo::xml::parseAttr(NAME, anon, 0, elem);\
		this->TO(anon);\
	} while(false);
	PARSE_BOOL_INT("anonymity", anonymity);
	PARSE_BOOL_INT("leaf", leaf);
	PARSE_BOOL_INT("fork", fork);
	PARSE_BOOL_INT("premium", premium);
#undef PARSE_BOOL_INT
	cinamo::xml::parseAttr("mail", this->mail_, std::string(""), elem);
	this->message ( elem->GetText() ? elem->GetText() : "" );

	if(log.t()){
		log.t(TAG, "Thread: %llu No:%llu vpos:%f Date:%llu Deleted:%llu Score:%llu UserId:%s Anon:%d Leaf:%d Premium:%d Fork:%d -> %s",
				this->thread(),
				this->no(),
				this->vpos(),
				this->date(),
				this->deleted(),
				this->score(),
				this->user_id().c_str(),
				this->anonymity(),
				this->leaf(),
				this->premium(),
				this->fork(),
				this->message().c_str()
				);
	}
}

Comment::Comment()
:thread_(0LLU)
,no_(0LLU)
,vpos_(-1)
,date_(0LLU)
,deleted_(0LLU)
,score_(0)
,user_id_("")
,message_("")
,mail_("")
,anonymity_(false)
,leaf_(false)
,premium_(false)
,fork_(false)
{
}

}}
