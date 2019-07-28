#ifndef __MALLALDDUCK_HPP_
#define __MALLALDDUCK_HPP_

#include "MiniDuckSimulator.hpp"

class MallardDuck:public Duck
{
public:
	MallardDuck():Duck(new FlyWithWings(),new Quack()){}
	void display()const
	{
		cout << "I'm a real MallardDuck" << endl;
	}
};

#endif