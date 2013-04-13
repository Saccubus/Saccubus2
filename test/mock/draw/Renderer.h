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
#include "../../../src/saccubus/draw/Renderer.h"

namespace samock {
namespace draw {

class Sprite;
class Renderer: public saccubus::draw::Renderer {
public:
	Renderer(cinamo::Logger& log);
	virtual ~Renderer();
public:
	const std::shared_ptr<saccubus::draw::Renderer*> handler() { return this->saccubus::draw::Renderer::handler(); };
public:
	virtual saccubus::draw::RawSprite* createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	virtual saccubus::draw::RawSprite* createRawSprite(int w, int h);
	virtual std::shared_ptr<saccubus::draw::Context> createContext(enum Format fmt, void* data, int w, int h, int stride);
	std::shared_ptr<saccubus::draw::Context> createContext();
};

}}
