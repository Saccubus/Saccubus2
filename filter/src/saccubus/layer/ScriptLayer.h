/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
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
