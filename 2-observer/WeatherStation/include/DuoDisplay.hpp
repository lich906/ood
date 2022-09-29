#pragma once
#include <iostream>

#include "IObservable.h"
#include "AbstractDuoDisplay.hpp"

class DuoDisplay : public AbstractDuoDisplay<WeatherInfo>
{
public:
	DuoDisplay() {}

	DuoDisplay(IObservable<WeatherInfo>* insideData, IObservable<WeatherInfo>* outsideData)
		: AbstractDuoDisplay(insideData, outsideData)
	{
	}

private:
	void DisplayInfo(const WeatherInfo& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

struct NumericStatsData
{
	double minimum = std::numeric_limits<double>::infinity();
	double maximum = -std::numeric_limits<double>::infinity();
	double accumulatedValue = 0;
};
