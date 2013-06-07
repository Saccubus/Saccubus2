/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <nekomata/system/System.h>

namespace nekomata{
namespace system {

Message::Message(enum Message::Type const type, float const vpos)
:type(type)
,vpos_(vpos)
{}

Comment::Comment(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
:Message(Message::COMMENT, vpos)
,message_(message)
,isYourPost_(isYourPost)
,mail_(mail)
,fromButton_(fromButton)
,isPremium_(isPremium)
,color_(color)
,size_(size)
,no_(no)
{

}

Script::Script(const float vpos, std::shared_ptr<const tree::Node> node)
:Message(Message::SCRIPT, vpos)
,node_(node)
{

}

bool Message::ComparatorByVpos::operator() (const Message& a, const Message& b)
{
	return a.vpos() < b.vpos();
}
bool Message::ComparatorByVpos::operator() (const Message& a, const float& b)
{
	return a.vpos() < b;
}
bool Message::ComparatorByVpos::operator() (const float& a, const Message& b)
{
	return a < b.vpos();
}
bool Message::ComparatorByVpos::operator() (const std::shared_ptr<const Message>& a, const std::shared_ptr<const Message>& b)
{
	return a->vpos() < b->vpos();
}
bool Message::ComparatorByVpos::operator() (const std::shared_ptr<const Message>& a, const float& b)
{
	return a->vpos() < b;
}
bool Message::ComparatorByVpos::operator() (const float& a, const std::shared_ptr<const Message>& b)
{
	return a < b->vpos();
}


}}
