/*
 * TimeLine.h
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */

#ifndef TIMELINE_H_
#define TIMELINE_H_

#include <vector>
#include <tr1/memory>
#include "../classdefs.h"
#include "../logging/Logging.h"
namespace nekomata{
namespace timeline
{

class TimePoint : public logging::Dumpable
{
private:
	float time;
	std::tr1::shared_ptr<const tree::ExprNode> node;
public:
	explicit TimePoint(const float time, const std::tr1::shared_ptr<const tree::ExprNode> node)
		:time(time), node(node){};
	TimePoint(const TimePoint& other)
		:time(other.time), node(other.node){};
	const bool operator<(const TimePoint other) const{return time < other.time;}
	const bool operator>(const TimePoint other) const{return time > other.time;}
	const bool operator<=(const TimePoint other) const{return time <= other.time;}
	const bool operator>=(const TimePoint other) const{return time >= other.time;}
	const bool operator==(const TimePoint other) const{return time == other.time;}
	const bool operator!=(const TimePoint other) const{return time != other.time;}
	virtual ~TimePoint(){}
	const float getTime() const{return time;}
	const std::tr1::shared_ptr<const tree::ExprNode> getNode() const{return node;}
	virtual void dump(logging::Dumper& dumper) const;
};

class TimeLine : public logging::Dumpable
{
private:
	std::vector<TimePoint> timePointList;
public:
	typedef std::vector<TimePoint>::const_iterator Iterator;
	TimeLine();
	virtual ~TimeLine();
	void insertLast(const float time, const std::tr1::shared_ptr<const tree::ExprNode> node);
	Iterator begin();
	Iterator end();
	size_t size();
	virtual void dump(logging::Dumper& dumper) const;
};

}
}
#endif /* TIMELINE_H_ */
