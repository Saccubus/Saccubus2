/*
 * Renderer.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef MOCK_RENDERER_H_
#define MOCK_RENDERER_H_

#include "../../../../saccubus/draw/Renderer.h"

namespace saccubus {
namespace mock {
namespace draw {

class Sprite;
class Renderer: public saccubus::draw::Renderer {
public:
	Renderer(logging::Logger& log);
	virtual ~Renderer();
private:
	std::vector<std::pair<std::pair<int, int>, Sprite* > > drawQuery;
public:
	typedef std::vector<std::pair<std::pair<int, int>, Sprite* > >::const_iterator QueryIterator;
public:
	void draw(int x, int y, Sprite* spr);
	QueryIterator queryBegin();
	QueryIterator queryEnd();
	std::size_t querySize();
	const std::tr1::shared_ptr<saccubus::draw::Renderer*> handler() { return this->saccubus::draw::Renderer::handler(); };
	virtual saccubus::draw::RawSprite* createRawSprite(int w, int h);};

}}}
#endif /* MOCK_RENDERER_H_ */
