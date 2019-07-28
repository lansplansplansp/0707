#ifndef __QUACKBEHAVIOR_HPP_
#define __QUACKBEHAVIOR_HPP_

#include "MiniDuckSimulator.hpp"

class QuackBehavior
{
public:
	virtual ~QuackBehavior() = 0;
	virtual void quack()const = 0;
};

QuackBehavior::~QuackBehavior()
{}

#endif