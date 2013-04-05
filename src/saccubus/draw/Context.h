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
