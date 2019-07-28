#ifndef __MINIDUCKSIMULATOR_HPP_
#define __MINIDUCKSIMULATOR_HPP_

#include <iostream>
#include <assert.h>
#include <memory>
#include "FlyBehavior.hpp"
#include "QuackBehavior.hpp"
#include "FlyWithWings.hpp"
#include "Quack.hpp"
//#include "Squack.hpp"
//#include "MuteQuack.hpp"
//#include "FakeQuack.hpp"

using namespace std;

class Duck
{
private:
	auto_ptr<FlyBehavior> _flyBehavior;
	auto_ptr<QuackBehavior> _quackBehavior;
	Duck(const Duck&);
	Duck& operator=(const Duck&);
protected:
	Duck(FlyBehavior *flyBehavior,QuackBehavior *quackBehavior):_flyBehavior(flyBehavior),_quackBehavior(quackBehavior)
	{
		assert(flyBehavior);
		assert(quackBehavior);
	}
	~Duck(){}
public:
	void setFlyBehavior(FlyBehavior *fb)
	{
		assert(fb);
		_flyBehavior = auto_ptr<FlyBehavior>(fb);
	}
	void setQuackBehavior(QuackBehavior *qb)
	{
		assert(qb);
		_quackBehavior = auto_ptr<QuackBehavior>(qb);
	}
	void performFly()const
	{
		_flyBehavior->fly();//没声明
	}
	void performQuack()const
	{
		_quackBehavior->quack();//没声明
	}
	void swim()const
	{
		cout << "All duck float, even decoys" << endl;
	}
	virtual void display() const = 0;
};

#endif