/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <vector>
#include <memory>
#include <cinamo/ClassUtil.h>
#include <nicomo/model/Comment.h>
#include "Layer.h"
#include "NekomataSystem.h"

namespace saccubus {
namespace layer {

class CommentLayer: public saccubus::layer::Layer {
	DEFINE_MEMBER(protected, private, layer::ThreadLayer*, thread);
	DEFINE_MEMBER(protected, private, bool, isForked);
public:
	CommentLayer(cinamo::Logger& log, layer::ThreadLayer* thread, bool isForked);
	virtual ~CommentLayer() = 0;
public:
	virtual void queueComment(std::shared_ptr<item::Comment> comment) = 0;
};

}}

