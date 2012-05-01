/**
 * Saccubus
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

#include "Comment.h"
namespace saccubus {
namespace layer {
namespace item {
bool Comment::StartTimeCompare::operator() (const Comment& a, const Comment& b)
{
	return a.from() < b.from();
}
bool Comment::StartTimeCompare::operator() (const Comment& a, const float& b)
{
	return a.from() < b;
}
bool Comment::StartTimeCompare::operator() (const float& a, const Comment& b)
{
	return a < b.from();
}
bool Comment::StartTimeCompare::operator() (const Comment* a, const Comment* b)
{
	return a->from() < b->from();
}
bool Comment::StartTimeCompare::operator() (const float& a, const Comment* b)
{
	return a < b->from();
}
bool Comment::StartTimeCompare::operator() (const Comment* a, const float& b)
{
	return a->from() < b;
}
bool Comment::StartTimeCompare::operator() (const std::tr1::shared_ptr<Comment>& a, const std::tr1::shared_ptr<Comment>& b)
{
	return a->from() < b->from();
}
bool Comment::StartTimeCompare::operator() (const float& a, const std::tr1::shared_ptr<Comment>& b)
{
	return a < b->from();
}
bool Comment::StartTimeCompare::operator() (const std::tr1::shared_ptr<Comment>& a, const float& b)
{
	return a->from() < b;
}

}}}
