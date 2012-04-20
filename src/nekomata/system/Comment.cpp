/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

bool Comment::isValid() const
{
	return type != INVALID;
}
bool Comment::hasScript() const
{
	return type == SCRIPT;
}
bool Comment::isComment() const
{
	return type == COMMENT;
}

bool Comment::ComparatorByVpos::operator() (const Comment& a, const Comment& b)
{
	return a.vpos() < b.vpos();
}
bool Comment::ComparatorByVpos::operator() (const Comment& a, const float& b)
{
	return a.vpos() < b;
}
bool Comment::ComparatorByVpos::operator() (const float& a, const Comment& b)
{
	return a < b.vpos();
}
bool Comment::ComparatorByVpos::operator() (const std::tr1::shared_ptr<const Comment>& a, const std::tr1::shared_ptr<const Comment>& b)
{
	return a->vpos() < b->vpos();
}
bool Comment::ComparatorByVpos::operator() (const std::tr1::shared_ptr<const Comment>& a, const float& b)
{
	return a->vpos() < b;
}
bool Comment::ComparatorByVpos::operator() (const float& a, const std::tr1::shared_ptr<const Comment>& b)
{
	return a < b->vpos();
}


}}
