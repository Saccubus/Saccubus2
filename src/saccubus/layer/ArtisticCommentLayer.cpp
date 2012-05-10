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
#include "ArtisticCommentLayer.h"
#include "item/Comment.h"
#include "ThreadLayer.h"
#include "../draw/Context.h"

namespace saccubus {
namespace layer {

const static std::string TAG("ArtisticCommentLayer");

const float ArtisticCommentLayer::CommentAheadTime = 1.0f;

ArtisticCommentLayer::ArtisticCommentLayer(logging::Logger& log, const std::map<std::string, std::string> & config, layer::ThreadLayer* thread, bool isForked)
:CommentLayer(log, thread, isForked)
,last(0)
{
}

ArtisticCommentLayer::~ArtisticCommentLayer()
{
}

void ArtisticCommentLayer::deploy(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const float vpos, std::tr1::shared_ptr<Slot> slot)
{
	slot->width(slot->comment()->width(ctx));
	slot->height(slot->comment()->height(ctx));
	switch(slot->comment()->placeY()){
	case item::Comment::Bottom:
		slot->y(ctx->height()-slot->height());
		break;
	default:
		slot->y(0);
		break;
	}

	bool running;
	do{
		running = false;
		for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
			std::tr1::shared_ptr<const Slot> other = *it;
			if(other->comment()->placeY() != slot->comment()->placeY()){
				continue;
			}
			if(other->y() + other->height() <= slot->y()){
				continue;
			}
			if(slot->y() + slot->height() <= other->y()){
				continue;
			}

			const float other_w = other->width();
			const float startTime = std::max(other->comment()->from(), slot->comment()->from());
			const float endTime = std::min(other->comment()->to(), slot->comment()->to());
			const float obj_x_t1 = getX(startTime, ctx->width(), slot);
			const float obj_x_t2 = getX(endTime, ctx->width(), slot);
			const float o_x_t1 = getX(startTime,ctx->width(), other);
			const float o_x_t2 = getX(endTime,ctx->width(), other);
			//当たり判定
			if ((obj_x_t1 <= o_x_t1 + other_w && o_x_t1 <= obj_x_t1 + slot->width())
				|| (obj_x_t2 <= o_x_t2 + other_w && o_x_t2 <= obj_x_t2 + slot->width())){
				if(slot->comment()->placeY() == item::Comment::Bottom){
					slot->y(other->y() - slot->height() - 1);
				}else{
					slot->y(other->y() + other->height() + 1);
				}
				running = true;
				break;
			}
		}
	} while(running);
	// 範囲外
	if(slot->y() < 0 || slot->y()+slot->height() > ctx->height()){
		slot->y(((rand() % 10000) * (ctx->height() - slot->height())) / 10000);
	}
	log.t(TAG, "Delployded: \"%s\" to -> %d, %d (size: %fx%f) time:%f->%f",slot->comment()->message().c_str(), slot->x(), slot->y(), slot->width(), slot->height(), slot->comment()->from(), slot->comment()->to());
	CommentIterator it = std::upper_bound(this->comments.begin(), this->comments.end(), slot, Slot::EndTimeComparator());
	this->comments.insert(it, slot);
}

float ArtisticCommentLayer::getX(float vpos, float screenWidth, std::tr1::shared_ptr<const Slot> slot)
{
	if(slot->comment()->placeY() != item::Comment::Middle){
		return (screenWidth - slot->width()) / 2;
	}else{
		float tmp = vpos - slot->comment()->from();
		return screenWidth - ((tmp * (screenWidth + slot->width())) / (slot->comment()->to()-slot->comment()->from()));
	}
}

void ArtisticCommentLayer::queueComment(std::tr1::shared_ptr<item::Comment> comment)
{
	DeployQueueIterator it = std::upper_bound(deployQueue.begin(), deployQueue.end(), comment, item::Comment::StartTimeCompare());
	deployQueue.insert(it, comment);

}
void ArtisticCommentLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	{ /* 表示しないコメントを削除 */
		CommentIterator beg = this->comments.begin();
		CommentIterator end = std::upper_bound(this->comments.begin(), this->comments.end(), vpos, ArtisticCommentLayer::Slot::EndTimeComparator());
		this->comments.erase(beg, end);
	}
	{ /* 実体の配置を計算 */
		DeployQueueIterator it = this->deployQueue.begin();
		for(; it != this->deployQueue.end(); ++it){
			std::tr1::shared_ptr<Slot> item(new Slot(*it));
			if(vpos < item->comment()->from()) break;
//			item->comment()->replace(thread()->nekoSystem);
			deploy(ctx, vpos, item);
		}
		this->deployQueue.erase(this->deployQueue.begin(), it);
	}
	{ /* 描画 */
		for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
			std::tr1::shared_ptr<Slot> item(*it);
			int x = static_cast<int>(getX(vpos, ctx->width(), item));
			item->x(x);
			item->comment()->draw(ctx, x, item->y());
		}
	}
}
bool ArtisticCommentLayer::onClick(int x, int y)
{
	for(CommentConstIterator it = this->comments.begin(); it != this->comments.end(); ++it){
		std::tr1::shared_ptr<const Slot> slot(*it);
		if(
				( slot->x() <= x && x <= slot->x()+slot->width() ) &&
				( slot->y() <= y && y <= slot->y()+slot->height() )
		){
			if(slot->comment()->onClick(x-slot->x(), y-slot->y())) return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
bool ArtisticCommentLayer::Slot::operator !=(const Slot& other)
{
	return this->comment() != other.comment();
}
bool ArtisticCommentLayer::Slot::operator ==(const Slot& other)
{
	return this->comment() == other.comment();
}

bool ArtisticCommentLayer::Slot::EndTimeComparator::operator() (const std::tr1::shared_ptr<const Slot>& a, const std::tr1::shared_ptr<const Slot>& b)
{
	return a->comment()->to() < b->comment()->to();
}
bool ArtisticCommentLayer::Slot::EndTimeComparator::operator() (const float& a, const std::tr1::shared_ptr<const Slot>& b)
{
	return a < b->comment()->to();
}
bool ArtisticCommentLayer::Slot::EndTimeComparator::operator() (const std::tr1::shared_ptr<const Slot>& a, const float& b)
{
	return a->comment()->to() < b;
}

ArtisticCommentLayer::Slot::Slot(std::tr1::shared_ptr<item::Comment> comment)
{
	this->comment(comment);
	this->x(-1);
	this->y(-1);
}
ArtisticCommentLayer::Slot::~Slot()
{
}

}}