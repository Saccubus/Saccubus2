/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
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
bool Comment::StartTimeCompare::operator() (const std::shared_ptr<Comment>& a, const std::shared_ptr<Comment>& b)
{
	return a->from() < b->from();
}
bool Comment::StartTimeCompare::operator() (const float& a, const std::shared_ptr<Comment>& b)
{
	return a < b->from();
}
bool Comment::StartTimeCompare::operator() (const std::shared_ptr<Comment>& a, const float& b)
{
	return a->from() < b;
}

}}}
