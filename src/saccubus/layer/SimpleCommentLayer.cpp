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

#include <algorithm>
#include "SimpleCommentLayer.h"
#include "item/Comment.h"
#include "item/CommentPipeLine.h"
#include "ThreadLayer.h"
#include "../draw/Context.h"


namespace saccubus {
namespace layer {

const float SimpleCommentLayer::CommentAheadTime = 1.0f;

SimpleCommentLayer::SimpleCommentLayer(logging::Logger& log, ThreadLayer* threadLayer, bool isForked)
:CommentLayer(log, threadLayer, isForked)
{
	// TODO Auto-generated constructor stub

}

SimpleCommentLayer::~SimpleCommentLayer() {
	// TODO Auto-generated destructor stub
}

void SimpleCommentLayer::doLayout(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const float vpos, LayoutData* layout)
{
	switch(layout->comment()->placeY()){
	case item::Comment::Bottom:
		layout->y(ctx->height()-layout->comment()->querySprite()->height());
		break;
	default:
		layout->y(0);
		break;
	}
	for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
		std::tr1::shared_ptr<const LayoutData> other = *it;
	}
}

float getX(float vpos, float screenWidth, item::Comment* comment)
{
	const float text_width = comment->querySprite()->width();
	if(comment->placeY() != item::Comment::Middle){
		return (screenWidth - text_width) / 2;
	}else{
		float tmp = vpos - comment->from();
		return screenWidth - ((tmp * (screenWidth + text_width)) / (comment->to()-comment->from()));
	}
}

void SimpleCommentLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	const float from = comments.size() > 0 ? comments.back()->comment()->orig()->vpos() : 0;
	{ /* 非表示のコメントを削除 */
		CommentIterator beg = this->comments.begin();
		CommentIterator end = std::upper_bound(this->comments.begin(), this->comments.end(), vpos, LayoutData::CommentEndTimeComparator());
		this->comments.erase(beg, end);
	}
	std::vector<const meta::Comment*> lst;
	this->threadLayer()->getCommentBetween(from, vpos+CommentAheadTime, isForked(), lst);
	for(std::vector<const meta::Comment*>::iterator it = lst.begin(); it != lst.end(); ++it){
		const meta::Comment* metaCom = *it;
		item::Comment* com = threadLayer()->pipeLine()->process(metaCom);
		LayoutData* item = new LayoutData(com);
	}


}
void SimpleCommentLayer::onClick(int x, int y)
{

}
//---------------------------------------------------------------------------------------------------------------------
bool LayoutData::operator !=(const LayoutData& other)
{
	return this->comment() != other.comment();
}
bool LayoutData::operator ==(const LayoutData& other)
{
	return this->comment() == other.comment();
}

bool LayoutData::CommentEndTimeComparator::operator() (const std::tr1::shared_ptr<const LayoutData>& a, const std::tr1::shared_ptr<const LayoutData>& b)
{
	return a->comment()->to() < b->comment()->to();
}
bool LayoutData::CommentEndTimeComparator::operator() (const float& a, const std::tr1::shared_ptr<const LayoutData>& b)
{
	return a < b->comment()->to();
}
bool LayoutData::CommentEndTimeComparator::operator() (const std::tr1::shared_ptr<const LayoutData>& a, const float& b)
{
	return a->comment()->to() < b;
}

LayoutData::LayoutData(item::Comment* comment)
{
	this->comment(comment);
}
LayoutData::~LayoutData()
{
	delete this->comment();
	this->comment(0);
}

}}
