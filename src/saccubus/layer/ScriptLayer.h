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
#include <nekomata/system/System.h>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>

#include "../classdefs.h"
#include "Layer.h"
#include "NekomataSystem.h"
#include "item/NekoItem.h"

namespace saccubus {
namespace layer {

class ScriptLayer final: public Layer {
	DEFINE_MEMBER(private, private, NekomataSystem*, nekoSystem);
private:
	void resolvePos(std::shared_ptr<saccubus::draw::Context> ctx, item::NekoItem* nekoItem, float screenWidth, float screenHeight, float* x, float* y);
public:
	ScriptLayer(cinamo::Logger& log, NekomataSystem* nekoSystem);
	virtual ~ScriptLayer() = default;
	/******************************************************************************************************************
	 * レイヤ
	 ******************************************************************************************************************/
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
	virtual void measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight);
};

}}
