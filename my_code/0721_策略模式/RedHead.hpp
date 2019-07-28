#ifndef __REHEAD_HPP_
#define __REHEAD_HPP_

#include "MiniDuckSimulator.hpp"

class RedHead:public Duck
{
public:
	RedHead():Duck(new FlyWithWings(),new Quack()){}
	void display()const
	{
		cout << "I'm a RedHead" << endl;
	}
};

#endif