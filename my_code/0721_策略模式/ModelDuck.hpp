#ifnedf __MODELDUCK_HPP_
#define __MODELDUCK_HPP_

#include "MiniDuckSimulator.hpp"

class ModelDuck:public Duck
{
public:
	ModelDuck():Duck(new FlyNoway(),new FakeQuack()){}
	void display()const
	{
		cout << "I'm model duck" << endl;
	}
};

#endif