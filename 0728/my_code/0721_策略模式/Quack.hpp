#ifndef __QUACK_HPP_
#define __QUACK_HPP_

#include "MiniDuckSimulator.hpp"
#include <iostream>

using namespace std;

class Quack:public QuackBehavior
{
public:
	void quack()const
	{
		cout << "Quack" << endl;
	}
};

#endif