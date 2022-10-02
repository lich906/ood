#include "include/WeatherData.hpp"
#include "Display/DuoDisplayPro.hpp"
#include "StatsDisplay/DuoStatsDisplayPro.hpp"

int main()
{
	WeatherData wd;

	DuoDisplayPro display;
	wd.RegisterObserver(display);

	DuoStatsDisplayPro statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 4, 180);
	wd.SetMeasurements(4, 0.8, 761, 8, 135);

	wd.RemoveObserver(statsDisplay);
	std::cout << "===========================" << std::endl;

	wd.SetMeasurements(10, 0.8, 761, 5, 90);
	wd.SetMeasurements(-10, 0.8, 761, 7, 270);
	return 0;
}
