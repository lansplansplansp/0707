#ifndef _FORECASTCONDITION_H_
#define _FORECASTCONDITION_H_

#include <iostream>
using namespace std;
#include "Observer.h"

class ForecastCondition:public Observer
{
public:
	ForecastCondition()
	{
		m_lastTemprature = 0.0;
		m_currentTemprature = 0.0;
		m_lastHumidity = 0.0;
		m_currentHumidity = 0.0;
		m_lastPressure = 0.0;
		m_currentPressure = 0.0;
	}
	~ForecastCondition(){}
	virtual void update(float temprature,float humidity,float pressure)
	{
		cout << "enter ForecastCondition update" << endl;
		m_lastTemprature = m_currentTemprature;
		m_currentTemprature = temprature;
		m_lastHumidity = m_currentHumidity;
		m_currentHumidity = humidity;
		m_lastPressure = m_currentPressure;
		m_currentPressure = pressure;
		display();
	}
	void display()
	{
		cout.setf(ios::showpoint);
		cout.precision(3);
		if(m_currentTemprature > m_lastTemprature)
		{
			cout << "m_currentTemprature:" <<m_currentTemprature <<"m_lastTemprature:"<<m_lastTemprature<< "Improving weather on the way" << endl;
		}
		else if(m_currentTemprature < m_lastTemprature)
		{
			cout << "Watch out for cooler,rain weather" << endl; 
		}
		else
		{
			cout << "More of the same" << endl;
		}
		
		if(m_currentHumidity > m_lastHumidity)
		{
			cout << "m_currentHumidity > m_lastHumidity" << endl;
		}
		else if(m_currentHumidity < m_lastHumidity)
		{
			cout << "m_currentHumidity < m_lastHumidity" << endl; 
		}
		else
		{
			cout << "More of the same" << endl;
		}
		
		if(m_currentPressure > m_lastPressure)
		{
			cout << "m_currentPressure > m_lastPressure" << endl;
		}
		else if(m_currentPressure < m_lastPressure)
		{
			cout << "m_currentPressure < m_lastPressure" << endl; 
		}
		else
		{
			cout << "More of the same" << endl;
		}	}
private:
	float m_lastTemprature;
	float m_currentTemprature;
	float m_lastHumidity;
	float m_currentHumidity;
	float m_lastPressure;
	float m_currentPressure;

	ForecastCondition(const ForecastCondition&);
	ForecastCondition& operator=(const ForecastCondition&);
};

#endif
