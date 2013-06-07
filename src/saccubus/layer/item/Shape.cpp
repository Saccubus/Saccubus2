/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Shape.h"
#include "../../draw/ShapeFactory.h"

namespace saccubus {
namespace layer {
namespace item {

Shape::Shape(nekomata::system::System& system, draw::ShapeFactory* shapeFactory)
:NekoItem(this)
,nekomata::system::Shape(system)
{
	this->shapeFactory(shapeFactory);
}

void Shape::onChanged()
{
	this->invalidate();
}
draw::Sprite::Handler<draw::Sprite> Shape::createSprite(std::shared_ptr<saccubus::draw::Context> ctx)
{
	return this->shapeFactory()->renderShape(ctx, this);
}
}}}
