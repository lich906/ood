#include "WindDirectionUtils.h"

std::optional<double> WindDirectionUtils::UpdateAverageWindDirection(const std::optional<double>& oldAverage, const std::optional<double>& current)
{
	if (current.has_value())
	{
		if (oldAverage.has_value())
		{
			double mid;
			if ((mid = abs(*current - *oldAverage)) > 180)
			{
				double average = (*current + *oldAverage) / 2;
				if (average > 180)
				{
					return average - 180;
				}
				else if (average < 180)
				{
					return average + 180;
				}
				else
				{
					return std::nullopt;
				}
			}
			else if (mid < 180)
			{
				return (*current + *oldAverage) / 2;
			}
			else
			{
				return std::nullopt;
			}
		}
		else
		{
			return current;
		}
	}
}
void WindDirectionUtils::DisplayAverageWindDirection(std::ostream& output, const std::optional<double>& avgWindDirection)
{
	if (avgWindDirection.has_value())
	{
		output << "Avg wind direction " << *avgWindDirection << std::endl;
	}
	else
	{
		output << "Avg wind direction -- calm" << std::endl;
	}
}
