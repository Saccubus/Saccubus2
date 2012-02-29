/*
 * TimeLine.cpp
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */

#include <algorithm>
#include <tr1/memory>
#include "TimeLine.h"
#include "../tree/Node.h"

namespace nekomata{
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

void TimeLine::insertLast(const float time, std::tr1::shared_ptr<const tree::ExprNode> node)
{
	TimePoint tp(time, node);
	std::vector<TimePoint>::iterator it = std::upper_bound(timePointList.begin(), timePointList.end(), tp);
	timePointList.insert(it, tp);
}

void TimeLine::merge(std::tr1::shared_ptr<TimeLine> other)
{
	for(Iterator it = other->begin(); it != other->end();++it){
		this->insertLast(it->getTime(), it->getNode());
	}
}

TimeLine::Iterator TimeLine::begin(float start)
{
	if(start != start){ //NaN判定
		return this->timePointList.begin();
	}else{
		std::tr1::shared_ptr<const tree::ExprNode> _null;
		TimePoint tp(start, _null);
		std::vector<TimePoint>::iterator it = std::lower_bound(timePointList.begin(), timePointList.end(), tp);
		return it;
	}
}
TimeLine::Iterator TimeLine::end(const float end)
{
	if(end != end){ //NaN判定
		return this->timePointList.end();
	}else{
		std::tr1::shared_ptr<const tree::ExprNode> _null;
		TimePoint tp(end, _null);
		std::vector<TimePoint>::iterator it = std::upper_bound(timePointList.begin(), timePointList.end(), tp);
		return it;
	}
}
size_t TimeLine::size() const
{
	return this->timePointList.size();
}
float TimeLine::getLastTime() const
{
	return this->timePointList.back().getTime();
}


void TimeLine::dump(logging::Dumper& dumper) const
{
	for(Iterator it = timePointList.begin();it!=this->timePointList.end();++it){
		(*it).dump(dumper);
	}
}

void TimePoint::dump(logging::Dumper& dumper) const
{
	dumper.printName("TimePoint");
	dumper.print("time", this->time);
	dumper.printNode("node", node);
}

}

}
