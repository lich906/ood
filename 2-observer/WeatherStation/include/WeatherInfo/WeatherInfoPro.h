#pragma once
#include <optional>

#include "WeatherInfo.h"

struct WeatherInfoPro : WeatherInfo
{
	const IObservable<WeatherInfoPro>* sourcePtr;
	double windSpeed = 0;
	std::optional<double> windDirection;
};