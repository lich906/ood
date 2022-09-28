#include "WeatherData.h"

int main()
{
	WeatherData wd;

	Display display;
	wd.RegisterObserver(display);

	StatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 3, 90);
	wd.SetMeasurements(4, 0.8, 761, 5, 270);

	//wd.RemoveObserver(statsDisplay);
	std::cout << "===========================" << std::endl;

	wd.SetMeasurements(10, 0.8, 761, 7, 350);
	wd.SetMeasurements(-10, 0.8, 761, 8, 90);
	return 0;
}