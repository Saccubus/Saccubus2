/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <vector>

namespace nekomata{
namespace machine{

template <typename T> class Stack
{
private:
	std::vector<T> stack;
public:
	inline T push(const T elm)
	{
		stack.push_back(elm);
		return elm;
	}

	inline T pop()
	{
		T val = stack.back();
		stack.pop_back();
		return val;
	}

	inline T top()
	{
		return stack.back();
	}

	inline T bottom()
	{
		return stack.front();
	}
	inline T replace(T elm)
	{
		T val = stack.back();
		stack.assign(stack.size()-1, elm);
		return val;
	}
	inline size_t size()
	{
		return stack.size();
	}
	typedef typename std::vector<T>::const_iterator Iterator;
	typedef typename std::vector<T>::reverse_iterator ReverseIterator;
	inline Iterator begin(){
		return stack.begin();
	}
	inline Iterator end(){
		return stack.end();
	}
	inline ReverseIterator rbegin(){
		return stack.rbegin();
	}
	inline ReverseIterator rend(){
		return stack.rend();
	}
	inline void merge(std::vector<T>& vec){
		vec.insert(vec.end(),stack.begin(), stack.end());
	}

public:
	explicit Stack(){}
	virtual ~Stack(){}
};

}}
