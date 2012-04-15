/*
 * classdefs.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SACCUBUS_CLASSDEFS_H_
#define SACCUBUS_CLASSDEFS_H_

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

namespace context{
class Comment;
}

namespace draw{
class Sprite;
class RawSprite;
class Renderer;
class CommentFactory;
}

namespace logging{
class Logger;
class Exception;
}

namespace layer{
class Layer;
class CommentLayer;
class ThreadLayer;
class VideoLayer;
}

namespace meta{
class Comment;
class ReplaceItem;
class ReplaceTable;
class Thread;
class MetaInfo;
class PlayInfo;
class Video;
}

namespace python{
class PyBridge;
}

namespace util{
class Bundle;
}

}
#endif /* SACCUBUS_CLASSDEFS_H_ */
