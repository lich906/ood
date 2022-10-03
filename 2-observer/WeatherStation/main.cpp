#include "include/WeatherData.hpp"
#include "Display/DuoDisplayPro.hpp"
#include "StatsDisplay/DuoStatsDisplayPro.hpp"
#include "Display/SimpleDisplay.hpp"

int main()
{
	WeatherData wd;

	SimpleDisplay simpleDisplay;

	DuoDisplayPro display;
	wd.CObservable<DataType::AllPro>::RegisterObserver(display);
	wd.CObservable<DataType::Temperature>::RegisterObserver(simpleDisplay);
	wd.CObservable<DataType::Pressure>::RegisterObserver(simpleDisplay, 0, true);

	DuoStatsDisplayPro statsDisplay;
	wd.CObservable<DataType::AllPro>::RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 4, 180);
	wd.SetMeasurements(4, 0.8, 761, 8, 135);

	wd.CObservable<DataType::AllPro>::RemoveObserver(statsDisplay);
	std::cout << "===========================" << std::endl;

	wd.SetMeasurements(10, 0.8, 761, 5, 90);
	wd.SetMeasurements(-10, 0.8, 761, 7, 270);
	return 0;
}
