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

#ifndef Saccubus_SIMPLECOMMENTLAYER_H__CPP_
#define Saccubus_SIMPLECOMMENTLAYER_H__CPP_

#include <tr1/memory>
#include "CommentLayer.h"
#include <vector>
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace layer {

class LayoutData{
	DEF_ATTR_ACCESSOR(public, public, int, y);
	DEF_ATTR_ACCESSOR(public, private, item::Comment*, comment);
private:
	LayoutData& operator=(const LayoutData& other){return *this;};
	LayoutData(const LayoutData& other){};
public:
	LayoutData(item::Comment* comment);
	virtual ~LayoutData();
public: /* setで比較する時用 */
	bool operator !=(const LayoutData& other);
	bool operator ==(const LayoutData& other);
public:
	struct CommentEndTimeComparator{
		bool operator() (const std::tr1::shared_ptr<const LayoutData>& a, const std::tr1::shared_ptr<const LayoutData>& b);
		bool operator() (const float& a, const std::tr1::shared_ptr<const LayoutData>& b);
		bool operator() (const std::tr1::shared_ptr<const LayoutData>& a, const float& b);
	};
};

class SimpleCommentLayer: public saccubus::layer::CommentLayer {
private:
	static const float CommentAheadTime;
private:
	std::vector<std::tr1::shared_ptr<LayoutData> > comments;
	typedef std::vector<std::tr1::shared_ptr<LayoutData> >::iterator CommentIterator;
	typedef std::vector<std::tr1::shared_ptr<LayoutData> >::const_iterator CommentConstIterator;
public:
	SimpleCommentLayer(logging::Logger& log, ThreadLayer* threadLayer, bool isForked);
	virtual ~SimpleCommentLayer();
public:
	virtual void draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual void onClick(int x, int y);
private:
	void doLayout(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const float vpos, std::tr1::shared_ptr<LayoutData> layout);
	float getX(float vpos, float screenWidth, item::Comment* comment);
};

}}
#endif /* INCLUDE_GUARD */
