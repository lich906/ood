#include "include/WeatherData.hpp"
#include "include/DuoDisplay.hpp"
#include "include/DuoStatsDisplay.hpp"

int main()
{
	WeatherData wd;

	DuoDisplay display;
	wd.RegisterObserver(display);

	DuoStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);
	std::cout << "===========================" << std::endl;

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}
