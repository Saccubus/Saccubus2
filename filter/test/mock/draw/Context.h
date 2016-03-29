/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once

#include <vector>
#include "Sprite.h"
#include "../../../src/saccubus/classdefs.h"
#include "../../../src/saccubus/draw/Context.h"

namespace samock {
namespace draw {

class Context: public saccubus::draw::Context {
public:
	Context(cinamo::Logger& log, std::shared_ptr<saccubus::draw::Renderer*> renderer);
	virtual ~Context();
private:
	std::vector<std::pair<std::pair<int, int>, Sprite* > > drawQuery;
public:
	typedef std::vector<std::pair<std::pair<int, int>, Sprite* > >::const_iterator QueryIterator;
public:
	virtual void draw(int x, int y, Sprite* spr);
	QueryIterator queryBegin();
	QueryIterator queryEnd();
	std::size_t querySize();
public:
	virtual float width() const;
	virtual float height() const;

};

}}
