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

#ifndef Saccubus_DRAW_CONTEXT_H__CPP_
#define Saccubus_DRAW_CONTEXT_H__CPP_

#include <tr1/memory>
#include "../classdefs.h"

namespace saccubus {
namespace draw {

class Context {
private:
	std::tr1::shared_ptr<Renderer*> _renderer;
protected:
	logging::Logger& log;
	Renderer* renderer();
public:
	Context(logging::Logger& log, std::tr1::shared_ptr<Renderer*> renderer);
	virtual ~Context();
public:
	virtual float width() const = 0;
	virtual float height() const = 0;
};

}}
#endif /* INCLUDE_GUARD */
