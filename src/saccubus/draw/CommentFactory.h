/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include "RawSprite.h"
namespace saccubus {
namespace draw {

class CommentFactory {
private:
	DEFINE_MEMBER(protected, private, Renderer*, renderer);
protected:
	cinamo::Logger& log;
public:
	CommentFactory(cinamo::Logger& log, Renderer* renderer);
	virtual ~CommentFactory();
public:
	virtual Sprite::Handler<Sprite> renderCommentText(std::shared_ptr<saccubus::draw::Context> ctx, const layer::item::Comment* comment) = 0;
	virtual saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> renderLabelText(std::shared_ptr<saccubus::draw::Context> ctx, const saccubus::layer::item::Label* label) = 0;
};

}}
