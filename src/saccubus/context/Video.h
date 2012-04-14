/*
 * Video.h
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#ifndef CONTEXT_VIDEO_H_
#define CONTEXT_VIDEO_H_

#include <vector>
#include "../classdefs.h"

namespace saccubus {
namespace context {

class Video {
private:
	python::PyBridge* const bridge;
	const meta::Video* const video;
	//最初にあるレイヤから描画する。つまり、一番最初のスレッドは一番下に描画される。
	std::vector<Thread*> threads;
public:
	Video(python::PyBridge* const bridge, const meta::Video* const video);
	virtual ~Video();
public:
	typedef std::vector<Thread*>::const_iterator ThreadIterator;
	ThreadIterator threadBegin() const;
	ThreadIterator threadEnd() const;
	std::size_t threadSize() const;
};

}}
#endif /* CONTEXT_VIDEO_H_ */
