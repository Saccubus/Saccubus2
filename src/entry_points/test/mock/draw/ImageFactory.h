/*
 * ImageFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef MOCK_DRAW_SPRITEFACTORY_H_
#define MOCK_DRAW_SPRITEFACTORY_H_

#include "../../../../saccubus/draw/ImageFactory.h"

namespace saccubus {
namespace mock {
namespace draw {

class ImageFactory: public saccubus::draw::ImageFactory {
public:
	ImageFactory();
	virtual ~ImageFactory();
protected:
	virtual saccubus::draw::RawSprite* createSprite(int w, int h);
};

}}}
#endif /* MOCK_DRAW_SPRITEFACTORY_H_ */
