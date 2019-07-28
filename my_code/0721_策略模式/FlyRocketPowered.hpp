#ifndef __FLYROCKETPOWERED_HPP_
#define	__FLYROCKETPOWERED_HPP_

#include "MiniDuckSimulator.hpp"
#include <iostream>

using namespace std;

class FlyRocketPowered:public FlyBehavior
{
public:
	void fly()const
	{
		cout << "I'm fly with a rocke"	<< endl;
	}
};

#endif