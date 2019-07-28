#ifndef __FLYWITHWINGS_HPP_
#define __FLYWITHWINGS_HPP_

#include "MiniDuckSimulator.hpp"
#include <iostream>

using namespace std;

class FlyWithWings:public FlyBehavior
{
public:
	void fly()const
	{
		cout << "I'm flying" << endl;
	}
};

#endif