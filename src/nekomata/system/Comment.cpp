/*
 * Comment.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#include <nekomata/system/System.h>

namespace nekomata{
namespace system {

Comment::Comment(const Comment& other)
:type(other.type)
,message_(other.message())
,vpos_(other.vpos())
,isYourPost_(other.isYourPost())
,mail_(other.mail())
,fromButton_(other.fromButton())
,isPremium_(other.isPremium())
,color_(other.color())
,size_(other.size())
,no_(other.no())
,node_(other.node())
{

}

Comment::Comment()
:type(INVALID)
,message_("")
,vpos_(NAN)
,isYourPost_(false)
,mail_("")
,fromButton_(false)
,isPremium_(false)
,color_(false)
,size_(false)
,no_(false)
,node_()
{

}
Comment::Comment(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
:type(COMMENT)
,message_(message)
,vpos_(vpos)
,isYourPost_(isYourPost)
,mail_(mail)
,fromButton_(fromButton)
,isPremium_(isPremium)
,color_(color)
,size_(size)
,no_(no)
,node_()
{

}

Comment::Comment(const float vpos, std::tr1::shared_ptr<const tree::Node> node)
:type(SCRIPT)
,message_("")
,vpos_(vpos)
,isYourPost_(false)
,mail_("")
,fromButton_(false)
,isPremium_(false)
,color_(false)
,size_(false)
,no_(false)
,node_(node)
{

}

}}
