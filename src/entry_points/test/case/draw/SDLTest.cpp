/*
 * SDLTest.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/draw/sdl/Sprite.h"
#include "../../../../saccubus/draw/sdl/Renderer.h"
#include "../../../../saccubus/draw/sdl/SimpleCommentFactory.h"
#include "../../../../saccubus/context/Comment.h"
#include "../../mock/meta/Comment.h"

using namespace saccubus::draw;
using namespace saccubus::context;
using namespace saccubus::mock;

namespace saccubus{
namespace test {
namespace draw{

TEST(SDLTest, QureyTest)
{
	mock::meta::Comment orig = mock::meta::Comment();
	orig.message("おいしいうどんが食べたいな");
	orig.mail("big");
	context::Comment comment = context::Comment(log_err, &orig);
	sdl::Renderer renderer(640, 480);
	sdl::SimpleCommentFactory factory(&renderer);

	Sprite::Handler<sdl::Sprite> spr;
	ASSERT_NO_THROW(spr = factory.renderComment(&comment).cast<sdl::Sprite>());
	ASSERT_GT(spr->width(), 0);
	ASSERT_GT(spr->height(), 0);
}


}}}
