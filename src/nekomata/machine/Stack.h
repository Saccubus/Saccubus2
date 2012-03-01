/*
 * Stack.h
 *
 *  Created on: 2012/02/11
 *	  Author: psi
 */

#ifndef STACK_H_
#define STACK_H_

namespace nekomata{
namespace machine
{
#include <vector>

template <typename T> class Stack
{
private:
	std::vector<T> stack;
public:
	T push(const T elm)
	{
		stack.push_back(elm);
		return elm;
	}

	T pop()
	{
		T val = stack.back();
		stack.pop_back();
		return val;
	}

	T top()
	{
		return stack.back();
	}

	T bottom()
	{
		return stack.front();
	}
	T replace(T elm)
	{
		T val = stack.back();
		stack.assign(stack.size()-1, elm);
		return val;
	}
	size_t size()
	{
		return stack.size();
	}
	typedef typename std::vector<T>::const_iterator Iterator;
	typedef typename std::vector<T>::reverse_iterator ReverseIterator;
	Iterator begin(){
		return stack.begin();
	}
	Iterator end(){
		return stack.end();
	}
	ReverseIterator rbegin(){
		return stack.rbegin();
	}
	ReverseIterator rend(){
		return stack.rend();
	}
	void merge(std::vector<T>& vec){
		vec.insert(vec.end(),stack.begin(), stack.end());
	}

public:
	explicit Stack(){}
	virtual ~Stack(){}
};

}
}
#endif /* STACK_H_ */
