/*
 * Renderer.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef RENDERER_H_
#define RENDERER_H_

namespace saccubus {
namespace renderer {

class Sprite
{

};

/**
 * 画面上に何かを描くものの基底クラス。
 */
class Renderer {
public:
	Renderer(){};
	virtual ~Renderer(){};
public:
	virtual Sprite* createTextSprite();
};

}}
#endif /* RENDERER_H_ */
