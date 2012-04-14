/*
 * Layer.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef LAYER_H_
#define LAYER_H_

#include "../draw/Canvas.h"

namespace saccubus {
namespace layer {

/**
 * コメントや図形の画面上の配置を計算したり、ニワン語との接続を行う、
 * いわゆるビジネスロジックを配置するクラス。
 * ！！　設計方針　！！
 * ！！　具体的な描画ライブラリに依存するコードは書いてはいけない　！！
 * ！！　それらはdraw名前空間以下のクラスに投げましょう　！！
 */
class Layer {
public:
	Layer();
	virtual ~Layer();
public:
	virtual void draw(float vpos, draw::Canvas* canvas) = 0;
};

}}
#endif /* LAYER_H_ */
