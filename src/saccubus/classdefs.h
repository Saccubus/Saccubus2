/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#pragma once

/**
 * *ちゅうい！*
 * このクラス一覧には、抽象的なクラス＊のみ＊記述する。
 * 実際の描画ライブラリや、配置ロジックに依存したクラスは、PluginOrganizerなどを用いて
 * 依存性注入すること。
 */
namespace saccubus{
class Saccubus;
class Adapter;
class PluginOrganizer;

namespace draw{
class Sprite;
class RawSprite;
class Renderer;
class Context;
class CommentFactory;
class ShapeFactory;
}

namespace logging{
class Exception;
}

namespace layer{
namespace item{
class Comment;
class Button;
class Label;
class Shape;
}
class Layer;
class CommentLayer;
class ThreadLayer;
class VideoLayer;
class NekomataSystem;
}

namespace python{
class PyBridge;
}

namespace util{
class Bundle;
}

}
