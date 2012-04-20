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

const static std::string TAG("SimpleCommentLayer");

const float SimpleCommentLayer::CommentAheadTime = 1.0f;

SimpleCommentLayer::SimpleCommentLayer(logging::Logger& log, ThreadLayer* threadLayer, bool isForked)
:CommentLayer(log, threadLayer, isForked)
,last(0)
{
}

SimpleCommentLayer::~SimpleCommentLayer()
{
}

void SimpleCommentLayer::doLayout(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const float vpos, std::tr1::shared_ptr<LayoutData> layout)
{
	switch(layout->comment()->placeY()){
	case item::Comment::Bottom:
		layout->y(ctx->height()-layout->comment()->querySprite()->height());
		break;
	default:
		layout->y(0);
		break;
	}
	const float w = layout->comment()->querySprite()->width();
	const float h = layout->comment()->querySprite()->height();
	bool running;
	do{
		running = false;
		for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
			std::tr1::shared_ptr<const LayoutData> other = *it;
			const float other_h = other->comment()->querySprite()->height();
			const float other_y = other->y();
			if(other->comment()->placeY() != layout->comment()->placeY()){
				continue;
			}
			if(other_y + other_h <= layout->y()){
				continue;
			}
			if(layout->y() + h <= other_y){
				continue;
			}

			const float other_w = other->comment()->querySprite()->width();
			const float startTime = std::max(other->comment()->from(), layout->comment()->from());
			const float endTime = std::min(other->comment()->to(), layout->comment()->to());
			const float obj_x_t1 = getX(startTime, ctx->width(), layout->comment());
			const float obj_x_t2 = getX(endTime, ctx->width(), layout->comment());
			const float o_x_t1 = getX(startTime,ctx->width(), other->comment());
			const float o_x_t2 = getX(endTime,ctx->width(), other->comment());
			//当たり判定
			if ((obj_x_t1 <= o_x_t1 + other_w && o_x_t1 <= obj_x_t1 + w)
				|| (obj_x_t2 <= o_x_t2 + other_w && o_x_t2 <= obj_x_t2 + w)){
				if(layout->comment()->placeY() == item::Comment::Bottom){
					layout->y(other_y - h - 1);
				}else{
					layout->y(other_y + other_h + 1);
				}
				running = true;
				break;
			}
		}
	} while(running);
	// 範囲外
	if(layout->y() < 0 || layout->y()+h > ctx->height()){
		layout->y(((rand() % 10000) * (ctx->height() - h)) / 10000);
	}
}

float SimpleCommentLayer::getX(float vpos, float screenWidth, item::Comment* comment)
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
	const float from = this->comments.size() > 0 ? this->comments.back()->comment()->orig()->vpos() : 0;
	if(vpos+CommentAheadTime < from){ // 逆方向シーク
		//TODO
	}
	{ /* 表示し終わったコメントを削除 */
		CommentIterator beg = this->comments.begin();
		CommentIterator end = std::upper_bound(this->comments.begin(), this->comments.end(), vpos, LayoutData::CommentEndTimeComparator());
		this->comments.erase(beg, end);
	}
	{ /* 新しいコメントを追加 */
		std::vector<const meta::Comment*> lst;
		this->threadLayer()->getCommentBetween(from, vpos+CommentAheadTime, isForked(), lst);
		for(std::vector<const meta::Comment*>::iterator it = lst.begin(); it != lst.end(); ++it){
			const meta::Comment* metaCom = *it;
			item::Comment* com = threadLayer()->pipeLine()->process(metaCom);

			std::tr1::shared_ptr<LayoutData> item(new LayoutData(com));
			doLayout(ctx, vpos, item);
			CommentIterator insertPoint = std::upper_bound(this->comments.begin(), this->comments.end(), item, LayoutData::CommentEndTimeComparator());
			this->comments.insert(insertPoint, item);
		}
	}
	{ /* 描画 */
		for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
			std::tr1::shared_ptr<LayoutData> item(*it);
			int x = static_cast<int>(getX(vpos, ctx->width(), item->comment()));
			item->x(x);
			item->comment()->querySprite()->draw(ctx, x, item->y());
		}
	}


}
bool SimpleCommentLayer::onClick(int x, int y)
{
	for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
		std::tr1::shared_ptr<const LayoutData> item(*it);
		if(
				( item->x() <= x && x <= item->x()+item->comment()->querySprite()->width() ) &&
				( item->y() <= y && y <= item->y()+item->comment()->querySprite()->height() )
		){
			if(item->comment()->onClick()) return true;
		}
	}
	return false;
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
	this->x(-1);
	this->y(-1);
}
LayoutData::~LayoutData()
{
	delete this->comment();
	this->comment(0);
}

}}
