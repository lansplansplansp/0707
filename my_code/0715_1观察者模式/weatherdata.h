#ifndef _WEATHER_DATA_H_
#define _WEATHER_DATA_H_

#include <iostream>
#include <list>
#include "Subject.h"
#include "Observer.h"
#include <assert.h>

using namespace std;

class WeatherData:public Subject
{
public:
	WeatherData()
	:m_temperature(0.0),m_humidity(0.0),m_pressure(0.0)
	{

	}
	~WeatherData(){}

	//weatherdata.registerObserver(&current);
	void registerObserver(Observer *subject)
	{
		cout << "enter registerObserver" << endl;
		assert(subject);
		m_observer.push_back(subject);
		cout << m_observer.size() << endl;
	}
	void removeObserver(Observer *subject)
	{
		m_observer.remove(subject);
		cout << m_observer.size() << endl;
		cout << "removeObserver success!" << endl;
	}
	void notifyObserver() const
	{
		cout << "enter notifyObserver" << endl;
		for(list<Observer *>::const_iterator iter = m_observer.begin();iter != m_observer.end();iter++)
		{
			Observer *obj = *iter;
			obj->update(m_temperature, m_humidity, m_pressure);
		}
	}
	void measurementsChanged()
	{
		notifyObserver();
	}
	void SetWeatherData(float temperture,float humidity,float pressure)
	{
		m_temperature = temperture;
		m_humidity = humidity;
		m_pressure = pressure;
		measurementsChanged();
		//cout << m_temperature << ' ' << m_humidity << ' ' << m_pressure << endl;
	}
	
private:
	float m_temperature;
	float m_humidity;
	float m_pressure;
	list<Observer *> m_observer;
	//禁止拷贝构造
	WeatherData(const WeatherData&);
	WeatherData& operator=(const WeatherData&);
};

#endif
