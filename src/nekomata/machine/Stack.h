/**
 * Nekomata
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
