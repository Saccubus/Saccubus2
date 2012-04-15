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
class ThreadLayer : public Layer {
private:
	draw::CommentFactory* commentFactory;
private:
	NekomataLayer* nekomataLayer;
	std::vector<CommentLayer*> commentLayers;
public:
	ThreadLayer(draw::Renderer* renderer, PluginOrganizer* organizer);
	virtual ~ThreadLayer();
public:
	virtual void draw(float vpos);
};

}}
#endif /* THREADLAYER_H_ */
