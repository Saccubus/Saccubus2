/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <nekomata/system/System.h>
#include "Item.h"

namespace saccubus {
namespace layer {
namespace item {

class NekoItem: public saccubus::layer::item::Item {
public:
	enum PosX{
		UndefinedX,
		CenterX,
		Right,
		Left
	};
	enum PosY{
		UndefinedY,
		CenterY,
		Top,
		Bottom
	};
	enum PosX _posX;
	enum PosY _posY;
	DEFINE_MEMBER(public, private, nekomata::system::Drawable*, drawable);
public:
	NekoItem(nekomata::system::Drawable* nekoDrawable);
	virtual ~NekoItem() noexcept = default;
public:
	virtual void invalidate();
	enum PosX posX();
	enum PosY posY();
private:
	void reload();
};

}}}
