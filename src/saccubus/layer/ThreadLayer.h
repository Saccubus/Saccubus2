/*
 * ThreadLayer.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef THREADLAYER_H_
#define THREADLAYER_H_

#include <vector>
#include "../classdefs.h"
#include "CommentLayer.h"
#include "NekomataLayer.h"

namespace saccubus {
namespace layer {

/**
 * スレッド1つ分のレイヤ
 * 複数のコメントレイヤと、猫又レイヤを持つ。
 */
class ThreadLayer {
private:
	draw::SpriteFactory* spriteFactory;
	draw::CommentFactory* commentFactory;
private:
	NekomataLayer* nekomataLayer;
	std::vector<CommentLayer*> commentLayers;
public:
	ThreadLayer(PluginOrganizer* organizer);
	virtual ~ThreadLayer();
public:
	virtual void draw(float vpos, draw::Canvas* canvas);
};

}}
#endif /* THREADLAYER_H_ */
