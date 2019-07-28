#ifndef __FLYBEHAVIOR_HPP_
#define __FLYBEHAVIOR_HPP_

#include "MiniDuckSimulator.hpp"

class FlyBehavior
{
public:
	virtual ~FlyBehavior() = 0;
	virtual void fly()const = 0;
};

FlyBehavior::~FlyBehavior()
{}

#endif