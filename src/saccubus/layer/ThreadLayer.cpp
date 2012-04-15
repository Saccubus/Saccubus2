/*
 * ThreadLayer.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "ThreadLayer.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/Renderer.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(PluginOrganizer* organizer) {
	this->renderer = organizer->newRenderer();
	this->commentFactory = organizer->newCommentFactory(this->renderer);

}

ThreadLayer::~ThreadLayer() {
	delete this->commentFactory;
	delete this->renderer;
}

void ThreadLayer::draw(float vpos, draw::Renderer* canvas)
{

}


}}
