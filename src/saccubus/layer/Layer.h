/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LAYER_H_
#define LAYER_H_

#include "../draw/Renderer.h"

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
	DEF_ATTR_ACCESSOR(protected, private, draw::Renderer*, renderer)
protected:
	logging::Logger& log;
public:
	Layer(logging::Logger& log, draw::Renderer* renderer);
	virtual ~Layer();
public:
	//指定されたサイズより大きなサイズが必要な場合は、適宜measured\w+を修正してください。
	virtual void measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight);
	//描画
	virtual void draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos) = 0;
	//クリックイベント
	virtual void onClick(int x, int y) = 0;
};

}}
#endif /* LAYER_H_ */
