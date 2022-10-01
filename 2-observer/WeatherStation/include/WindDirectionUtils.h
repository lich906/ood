#pragma once
#include <optional>
#include <iostream>

class WindDirectionUtils
{
public:
	static std::optional<double> UpdateAverageWindDirection(const std::optional<double>& oldAverage, const std::optional<double>& current);

	static void DisplayAverageWindDirection(std::ostream& output, const std::optional<double>& avgWindDirection);
};
