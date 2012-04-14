/*
 * classdefs.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SACCUBUS_CLASSDEFS_H_
#define SACCUBUS_CLASSDEFS_H_

namespace saccubus{
class Saccubus;
class Adapter;

namespace context{
class VideoContext;
class ThreadContext;
}

namespace draw{
class Sprite;
class Canvas;
class SpriteFactory;
class CommentFactory;
}

namespace logging{
class Logger;
class Exception;
}

namespace Layer{
class Layer;
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
