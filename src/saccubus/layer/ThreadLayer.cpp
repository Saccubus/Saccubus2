/*
 * ThreadLayer.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "ThreadLayer.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/SpriteFactory.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(PluginOrganizer* organizer) {
	this->spriteFactory = organizer->newSpriteFactory();
	this->commentFactory = organizer->newCommentFactory(this->spriteFactory);

}

ThreadLayer::~ThreadLayer() {
	delete this->commentFactory;
	delete this->spriteFactory;
}

void ThreadLayer::draw(float vpos, draw::Canvas* canvas)
{

}


}}
