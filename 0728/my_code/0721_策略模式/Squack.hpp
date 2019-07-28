#ifndef __SQUACK_HPP_
#define __SQUACK_HPP_

#include "MiniDuckSimulator.hpp"
#include <iostream>

using namespace std;

class Squack
{
public:
	void quack()const
	{
		cout << "Squack" << endl;
	}
};

#endif