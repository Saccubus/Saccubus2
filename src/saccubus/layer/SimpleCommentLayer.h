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
#include <memory>
#include <vector>
#include <set>
#include <cinamo/ClassUtil.h>
#include "CommentLayer.h"

namespace saccubus {
namespace layer {

class SimpleCommentLayer final: public saccubus::layer::CommentLayer {
private:
	class Slot{
		DEFINE_MEMBER(public, public, int, y);
		DEFINE_MEMBER(public, public, int, x);
		DEFINE_MEMBER(public, public, float, width);
		DEFINE_MEMBER(public, public, float, height);
		DEFINE_MEMBER(public, private, std::shared_ptr<item::Comment>, comment);
	private:
		Slot& operator=(const Slot& other){return *this;};
		Slot(const Slot& other){};
	public:
		Slot(std::shared_ptr<item::Comment> comment);
		virtual ~Slot();
	public: /* setで比較する時用 */
		bool operator !=(const Slot& other);
		bool operator ==(const Slot& other);
	public:
		struct EndTimeComparator{
			bool operator() (const std::shared_ptr<const Slot>& a, const std::shared_ptr<const Slot>& b);
			bool operator() (const float& a, const std::shared_ptr<const Slot>& b);
			bool operator() (const std::shared_ptr<const Slot>& a, const float& b);
		};
	};
private:
	static const float CommentAheadTime;
private:
	std::vector<std::shared_ptr<item::Comment> > deployQueue;
	typedef std::vector<std::shared_ptr<item::Comment> >::iterator DeployQueueIterator;
	std::vector<std::shared_ptr<Slot> > comments;
	typedef std::vector<std::shared_ptr<Slot> >::iterator CommentIterator;
	typedef std::vector<std::shared_ptr<Slot> >::const_iterator CommentConstIterator;
public:
	SimpleCommentLayer(cinamo::Logger& log, const std::map<std::string, std::string> & config, layer::ThreadLayer* thread, bool isForked);
	virtual ~SimpleCommentLayer() = default;
	float last;
public:
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
	virtual void queueComment(std::shared_ptr<item::Comment> comment);
private:
	void deploy(std::shared_ptr<saccubus::draw::Context> ctx, const float vpos, std::shared_ptr<Slot> layout);
	float getX(float vpos, float screenWidth, std::shared_ptr<const Slot> layout);
};

}}
