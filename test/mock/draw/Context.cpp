/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Context.h"

namespace samock {
namespace draw {

Context::Context(cinamo::Logger& log, std::shared_ptr<saccubus::draw::Renderer*> renderer)
:saccubus::draw::Context(log, renderer)
{
}

Context::~Context() {
}

void Context::draw(int x, int y, Sprite* spr)
{
	this->drawQuery.push_back(std::pair<std::pair<int,int>,Sprite* >(std::pair<int, int>(x, y), spr));
}

Context::QueryIterator Context::queryBegin()
{
	return this->drawQuery.begin();
}
Context::QueryIterator Context::queryEnd()
{
	return this->drawQuery.end();
}
std::size_t Context::querySize()
{
	return this->drawQuery.size();
}

float Context::width() const
{
	return 640;
}
float Context::height() const
{
	return 480;
}


}}
