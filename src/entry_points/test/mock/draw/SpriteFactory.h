/*
 * SpriteFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef MOCK_DRAW_SPRITEFACTORY_H_
#define MOCK_DRAW_SPRITEFACTORY_H_

#include "../../../../saccubus/draw/SpriteFactory.h"

namespace saccubus {
namespace mock {
namespace draw {

class SpriteFactory: public saccubus::draw::SpriteFactory {
public:
	SpriteFactory();
	virtual ~SpriteFactory();
protected:
	virtual saccubus::draw::RawSprite* createSprite(int w, int h);
};

}}}
#endif /* MOCK_DRAW_SPRITEFACTORY_H_ */
