#ifndef _CURRENTCONDITION_H_
#define _CURRENTCONDITION_H_

#include <iostream>
using namespace std;
#include "Observer.h"

class CurrentCondition:public Observer
{
public:
	CurrentCondition():m_temprature(0.0),m_humidity(0.0),m_pressure(0.0)
	{
		
	}
	~CurrentCondition(){}
	void display()
	{
		cout.setf(ios::showpoint);
		cout.precision(3);
		cout << "Current condition: " << m_temprature << "C " <<  m_humidity << "% " << m_pressure << "Pa" << endl;
	}	
	virtual void update(float temprature,float humidity,float pressure)
	{
		cout << "enter CurrentCondition update" << endl;

		m_temprature = temprature;
		m_humidity = humidity;
		m_pressure = pressure;
		display();
	}

private:
	float m_temprature;
	float m_humidity;
	float m_pressure;
	//禁止拷贝构造
	CurrentCondition(const CurrentCondition&);
	CurrentCondition& operator=(const CurrentCondition&);
};

#endif
