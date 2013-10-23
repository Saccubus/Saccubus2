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

Comment::Comment(std::string const& message, double vpos, bool isYourPost, std::string const& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
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

}}
