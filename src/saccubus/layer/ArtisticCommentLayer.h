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
#pragma once
#include <tr1/memory>
#include "CommentLayer.h"
#include <vector>
#include <set>
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace layer {

class ArtisticCommentLayer: public saccubus::layer::CommentLayer {
private:
	class Slot{
		DEF_ATTR_ACCESSOR(public, public, int, y);
		DEF_ATTR_ACCESSOR(public, public, int, x);
		DEF_ATTR_ACCESSOR(public, public, float, width);
		DEF_ATTR_ACCESSOR(public, public, float, height);
		DEF_ATTR_ACCESSOR(public, private, std::tr1::shared_ptr<item::Comment>, comment);
	private:
		Slot& operator=(const Slot& other){return *this;};
		Slot(const Slot& other){};
	public:
		Slot(std::tr1::shared_ptr<item::Comment> comment);
		virtual ~Slot();
	public: /* setで比較する時用 */
		bool operator !=(const Slot& other);
		bool operator ==(const Slot& other);
	public:
		struct EndTimeComparator{
			bool operator() (const std::tr1::shared_ptr<const Slot>& a, const std::tr1::shared_ptr<const Slot>& b);
			bool operator() (const float& a, const std::tr1::shared_ptr<const Slot>& b);
			bool operator() (const std::tr1::shared_ptr<const Slot>& a, const float& b);
		};
	};
private:
	static const float CommentAheadTime;
private:
	std::vector<std::tr1::shared_ptr<item::Comment> > deployQueue;
	typedef std::vector<std::tr1::shared_ptr<item::Comment> >::iterator DeployQueueIterator;
	std::vector<std::tr1::shared_ptr<Slot> > comments;
	typedef std::vector<std::tr1::shared_ptr<Slot> >::iterator CommentIterator;
	typedef std::vector<std::tr1::shared_ptr<Slot> >::const_iterator CommentConstIterator;
public:
	ArtisticCommentLayer(logging::Logger& log, const std::map<std::string, std::string> & config, layer::ThreadLayer* thread, bool isForked);
	virtual ~ArtisticCommentLayer();
	float last;
public:
	virtual void draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
	virtual void queueComment(std::tr1::shared_ptr<item::Comment> comment);
private:
	void deploy(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const float vpos, std::tr1::shared_ptr<Slot> layout);
	float getX(float vpos, float screenWidth, std::tr1::shared_ptr<const Slot> layout);
};

}}
