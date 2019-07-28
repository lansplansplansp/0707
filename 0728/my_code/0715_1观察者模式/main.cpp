#include "weatherdata.h"
#include "Currentcondition.h"
#include "Forecastcondition.h"

int main()
{
	CurrentCondition current;
	ForecastCondition forecast;
	WeatherData weatherdata;
	
	
	weatherdata.registerObserver(&current);
	weatherdata.registerObserver(&forecast);
	weatherdata.removeObserver(&current);
	 	
	weatherdata.SetWeatherData(15,65,30.4f);
	weatherdata.SetWeatherData(14,65,30.4f);

	return 0;
}
