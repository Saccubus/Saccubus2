/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Logger.h>
#include <memory>
#include "../NicoConstant.h"
#include "../classdefs.h"

namespace saccubus {
namespace draw {

class Context {
private:
	std::shared_ptr<Renderer*> _renderer;
protected:
	cinamo::Logger& log;
	Renderer* renderer();
public:
	Context(cinamo::Logger& log, std::shared_ptr<Renderer*> renderer);
	virtual ~Context();
public:
	virtual float width() const = 0;
	virtual float height() const = 0;
	float factor() const { return this->height()/nico::ScreenHeight; };
};

}}
