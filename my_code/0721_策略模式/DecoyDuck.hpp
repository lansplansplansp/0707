#ifndef __DECOYDUCK_HPP_
#define __DECOYDUCK_HPP_

#include "MiniDuckSimulator.hpp"

class DecoyDuck:public Duck
{
public:
	DecoyDuck():Duck(new FlyNoway(),new MuteQuack()){}
	void display()const
	{
		cout << "I'm a duck decoy" << endl;
	}
};

#endif