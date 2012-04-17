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

ThreadLayer::ThreadLayer(logging::Logger& log, draw::Renderer* renderer, PluginOrganizer* organizer)
:Layer(log, renderer)
{
	this->commentFactory = organizer->newCommentFactory(this->renderer());

}

ThreadLayer::~ThreadLayer() {
	delete this->commentFactory;
}

void ThreadLayer::draw(float vpos)
{

}


}}
