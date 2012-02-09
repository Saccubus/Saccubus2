/*
 * TimeLine.cpp
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */

#include "TimeLine.h"
#include <algorithm>

namespace timeline
{

TimeLine::TimeLine()
{
	// TODO Auto-generated constructor stub

}

TimeLine::~TimeLine()
{
	// TODO Auto-generated destructor stub
}

void TimeLine::insertLast(const float time, const std::tr1::shared_ptr<const tree::ExprNode> node)
{
	TimePoint tp(time, node);
	std::vector<TimePoint>::iterator it = std::upper_bound(timePointList.begin(), timePointList.end(), tp);
	timePointList.insert(it, tp);
}

TimeLine::Iterator TimeLine::begin()
{
	return this->timePointList.begin();
}
TimeLine::Iterator TimeLine::end()
{
	return this->timePointList.end();
}
size_t TimeLine::size()
{
	return this->timePointList.size();
}

}

 /* namespace machine */
