#include "WindDirectionUtils.h"

std::optional<double> WindDirectionUtils::UpdateAverageWindDirection(const std::optional<double>& oldAverage, const std::optional<double>& current)
{
	if (current.has_value() && oldAverage.has_value())
	{
		double sinSum = std::sin(DegToRad(*oldAverage)) + std::sin(DegToRad(*current));
		double cosSum = std::cos(DegToRad(*oldAverage)) + std::cos(DegToRad(*current));
		double updatedAverage = RadToDeg(std::atan2(sinSum, cosSum)) + 360.0;
		return std::fmod(updatedAverage, 360);
	}
	else
	{
		return current;
	}
}
void WindDirectionUtils::DisplayWindDirection(std::ostream& output, const std::optional<double>& avgWindDirection)
{
	if (avgWindDirection.has_value())
	{
		output << *avgWindDirection;
	}
	else
	{
		output << "calm";
	}
}

double WindDirectionUtils::DegToRad(double deg)
{
	return M_PI * deg / 180.0;
}

double WindDirectionUtils::RadToDeg(double rad)
{
	return 180.0 * rad / M_PI;
}
