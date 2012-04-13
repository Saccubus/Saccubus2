/*
 * VideoContext.h
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#ifndef VIDEOCONTEXT_H_
#define VIDEOCONTEXT_H_

#include <vector>
#include "../classdefs.h"

namespace saccubus {
namespace context {

class VideoContext {
private:
	python::PyBridge* const bridge;
	const meta::Video* const video;
	//最初にあるレイヤから描画する。つまり、一番最初のスレッドは一番下に描画される。
	std::vector<ThreadContext*> threads;
public:
	VideoContext(python::PyBridge* const bridge, const meta::Video* const video);
	virtual ~VideoContext();
public:
	typedef std::vector<ThreadContext*>::const_iterator ThreadIterator;
	ThreadIterator threadBegin() const;
	ThreadIterator threadEnd() const;
	std::size_t threadSize() const;
};

}}
#endif /* VIDEOCONTEXT_H_ */
