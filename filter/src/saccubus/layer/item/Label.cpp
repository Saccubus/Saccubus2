/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Label.h"
#include "Comment.h"
#include "../../draw/CommentFactory.h"

namespace saccubus {
namespace layer {
namespace item {

Label::Label(nekomata::system::System& system, draw::CommentFactory* commentFactory)
: NekoItem(this), nekomata::system::Label(system)
{
	this->commentFactory(commentFactory);
}

void Label::onChanged()
{
	this->invalidate();
}
draw::Sprite::Handler<draw::Sprite> Label::createSprite(std::shared_ptr<saccubus::draw::Context> ctx)
{
	return this->commentFactory()->renderLabelText(ctx, this);
}

}}}
