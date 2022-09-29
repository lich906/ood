#pragma once
#include <optional>

struct WeatherInfoPro
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	std::optional<double> windDirection;
};