/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <vector>
#include <nekomata/Nekomata.h>
#include <nicomo/Model.h>
#include "../classdefs.h"
#include "NekomataSystem.h"
#include "CommentLayer.h"
#include "ScriptLayer.h"

namespace saccubus {
namespace layer {
namespace item {
class CommentPipeLine;
}

/**
 * スレッド1つ分のレイヤ
 * 複数のコメントレイヤと、猫又レイヤを持つ。
 */
class ThreadLayer : public Layer {
	DEFINE_MEMBER(public, private, draw::CommentFactory*, commentFactory);
	DEFINE_MEMBER(public, private, draw::ShapeFactory*, shapeFactory);
	DEFINE_MEMBER(public, private, NekomataSystem*, nekoSystem);
private:
	const nicomo::model::Thread& thread;
	const std::string ngScript;
	python::PyBridge* bridge;
private:
	nekomata::logging::Logger* nekoLogger;
	nekomata::Nekomata* neko;
private:
	ScriptLayer* scriptLayer;
	CommentLayer* localCommentLayer;
	CommentLayer* mainCommentLayer;
	CommentLayer* forkedCommentLayer;
public:
	ThreadLayer(cinamo::Logger& log, const nicomo::model::Thread& thread, std::string const& ngScript, python::PyBridge* bridge, const nicomo::model::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* organizer);
	virtual ~ThreadLayer();
public:
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
	virtual void measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight);
};

}}
