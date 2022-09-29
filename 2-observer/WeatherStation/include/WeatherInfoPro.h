#pragma once
#include <optional>

#include "WeatherInfo.h"

struct WeatherInfoPro : WeatherInfo
{
	double windSpeed = 0;
	std::optional<double> windDirection;
};