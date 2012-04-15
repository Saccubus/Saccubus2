/*
 * CommentFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "CommentFactory.h"

namespace saccubus {
namespace draw {

CommentFactory::CommentFactory(ImageFactory* imgFactory)
{
	this->imgFactory(imgFactory);
}

CommentFactory::~CommentFactory() {
	// TODO Auto-generated destructor stub
}

}}

