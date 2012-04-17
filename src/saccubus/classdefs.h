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
namespace item{
class Comment;
}
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
