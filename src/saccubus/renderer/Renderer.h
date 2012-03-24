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

/**
 * 画面上に何かを描くものの基底クラス。
 * RenderCtx: 実装する際に実際に使うコンテキスト。SDLならSDL_Surfaceとかね。
 */
template <typename RenderCtx>
class Renderer {
public:
	Renderer(){};
	virtual ~Renderer(){};
	virtual void render(RenderCtx* ctx) = 0;
};

}}
#endif /* RENDERER_H_ */
