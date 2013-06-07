/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <nekomata/system/System.h>
#include "NekoItem.h"

namespace saccubus {
namespace layer {
namespace item {

class Shape: public saccubus::layer::item::NekoItem, public nekomata::system::Shape
{
	DEFINE_MEMBER(protected, private, draw::ShapeFactory*, shapeFactory);
public:
	Shape(nekomata::system::System& system, draw::ShapeFactory* shapeFactory);
	virtual ~Shape() noexcept = default;
	virtual void onChanged();
protected:
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::shared_ptr<saccubus::draw::Context> ctx);
};

}}}
