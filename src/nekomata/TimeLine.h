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
#include <cmath>
#include <algorithm>
namespace nekomata {

template <typename T>
class TimePoint
{
private:
	float time;
	std::tr1::shared_ptr<T> data;
public:
	explicit TimePoint(const float time, const std::tr1::shared_ptr<T> data)
		:time(time), data(data){};
	TimePoint(const TimePoint& other)
		:time(other.time), data(other.data){};
	const bool operator<(const TimePoint other) const{return time < other.time;}
	const bool operator>(const TimePoint other) const{return time > other.time;}
	const bool operator<=(const TimePoint other) const{return time <= other.time;}
	const bool operator>=(const TimePoint other) const{return time >= other.time;}
	const bool operator==(const TimePoint other) const{return time == other.time;}
	const bool operator!=(const TimePoint other) const{return time != other.time;}
	virtual ~TimePoint(){}
	const float getTime() const{return time;}
	const std::tr1::shared_ptr<T> getData() const{return data;}
};

template <typename T>
class TimeLine
{
private:
	std::vector<TimePoint<T> > timePointList;
public:
	typedef typename std::vector<TimePoint<T> >::const_iterator Iterator;
	TimeLine(){}
	virtual ~TimeLine(){}
	void insertLast(const float time, std::tr1::shared_ptr<T> node)
	{
		TimePoint<T> tp(time, node);
		typename std::vector<TimePoint<T> >::iterator it = std::upper_bound(timePointList.begin(), timePointList.end(), tp);
		timePointList.insert(it, tp);
	}

	void merge(std::tr1::shared_ptr<TimeLine<T> > other)
	{
		for(Iterator it = other->begin(); it != other->end();++it){
			this->insertLast(it->getTime(), it->getNode());
		}
	}
	Iterator begin(float start=NAN)
	{
		if(start != start){ //NaN判定
			return this->timePointList.begin();
		}else{
			std::tr1::shared_ptr<T> _null;
			TimePoint<T> tp(start, _null);
			Iterator it = std::lower_bound(timePointList.begin(), timePointList.end(), tp);
			return it;
		}
	}
	Iterator end(float end=NAN)
	{
		if(end != end){ //NaN判定
			return this->timePointList.end();
		}else{
			std::tr1::shared_ptr<T> _null;
			TimePoint<T> tp(end, _null);
			Iterator it = std::upper_bound(timePointList.begin(), timePointList.end(), tp);
			return it;
		}
	}
	size_t size() const
	{
		return this->timePointList.size();
	}
	float getLastTime() const
	{
		return this->timePointList.back().getTime();
	}
};

}
#endif /* TIMELINE_H_ */
