#ifndef __FLYNOWAY_HPP_
#define __FLYNOWAY_HPP_

#include "MiniDuckSimulator.hpp"
#include <iostream>

using namespace std;

class FlyNoway:public FlyBehavior
{
public:
	void fly()const
	{
		cout << "I can't fly" << endl;
	}
};

#endif