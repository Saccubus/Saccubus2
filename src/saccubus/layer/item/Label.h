/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <nekomata/system/System.h>
#include "NekoItem.h"
#include "Comment.h"

namespace saccubus {
namespace layer {
namespace item {

class Label: public saccubus::layer::item::NekoItem, public nekomata::system::Label {
	DEFINE_MEMBER(private, private, draw::CommentFactory*, commentFactory);
public:
	explicit Label(nekomata::system::System& system, draw::CommentFactory* commentFactory);
	virtual ~Label() noexcept = default;
	virtual void onChanged();
protected:
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::shared_ptr<saccubus::draw::Context> ctx);
};

}}}
