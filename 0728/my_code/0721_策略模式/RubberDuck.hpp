#ifndef __RUBBERDUCK_HPP_
#define __RUBBERDUCK_HPP_

#include "MiniDuckSimulator.hpp"

class RubberDuck:public Duck
{
public:
	RubberDuck():Duck(new FlyNoway(),new Squack()){}
	void display()const 
	{
		cout << "I'm a RubberDuck" << endl;
	}
};

#endif