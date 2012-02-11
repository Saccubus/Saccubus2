/*
 * Stack.h
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#ifndef STACK_H_
#define STACK_H_

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
    	T val = this->pop();
    	push(elm);
    	return val;
    }
public:
	Stack(){}
	virtual ~Stack(){}
};

} /* namespace machine */
#endif /* STACK_H_ */
