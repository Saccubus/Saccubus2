/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Logger.h>
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
protected:
	cinamo::Logger& log;
public:
	Layer(cinamo::Logger& log);
	virtual ~Layer() = 0;
public:
	//wとhが指定されたサイズです。measuredWidthやmeasuredHeightにレイヤが必要とするサイズを指定してください。
	virtual void measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight);
	//描画
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos) = 0;
	//クリックイベント
	// イベントが消費される場合はtrue、下レイヤのボタンにイベントが透過する場合はfalseを返す。
	virtual bool onClick(int x, int y) = 0;
};

}}
