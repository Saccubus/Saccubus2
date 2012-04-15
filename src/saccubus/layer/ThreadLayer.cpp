/*
 * ThreadLayer.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "ThreadLayer.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/ImageFactory.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(PluginOrganizer* organizer) {
	this->imageFactory = organizer->newImageFactory();
	this->commentFactory = organizer->newCommentFactory(this->imageFactory);

}

ThreadLayer::~ThreadLayer() {
	delete this->commentFactory;
	delete this->imageFactory;
}

void ThreadLayer::draw(float vpos, draw::Canvas* canvas)
{

}


}}
