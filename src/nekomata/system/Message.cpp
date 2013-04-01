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
