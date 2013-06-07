/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
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
