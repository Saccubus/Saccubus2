/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "CommentLayer.h"

namespace saccubus {
namespace layer {

CommentLayer::CommentLayer(cinamo::Logger& log, layer::ThreadLayer* thread, bool isForked)
:Layer(log)
,thread_(nullptr)
,isForked_(false)
{
	this->thread(thread);
	this->isForked(isForked);
}

CommentLayer::~CommentLayer() {
}


}}
