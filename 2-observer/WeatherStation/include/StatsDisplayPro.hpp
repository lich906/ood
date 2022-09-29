#pragma once
#include <iostream>

#include "WeatherInfoPro.h"
#include "IObserver.h"
#include "NumericStatsData.h"

class StatsDisplayPro : public IObserver<WeatherInfoPro>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(const WeatherInfoPro& data) override
	{
		UpdateNumericStatsData(data.temperature, m_temperatureStats);
		UpdateNumericStatsData(data.humidity, m_humidityStats);
		UpdateNumericStatsData(data.pressure, m_pressureStats);
		UpdateNumericStatsData(data.windSpeed, m_windSpeedStats);
		UpdateAverageWindDirection(data.windDirection);

		++m_count;

		DisplayNumericStatsData(m_temperatureStats, "Temperature");
		DisplayNumericStatsData(m_humidityStats, "Humidity");
		DisplayNumericStatsData(m_pressureStats, "Pressure");
		DisplayNumericStatsData(m_windSpeedStats, "Wind Speed");
		DisplayAverageWindDirection();
	}

	void UpdateNumericStatsData(double current, NumericStatsData& statsData) const
	{
		// std::min
		if (statsData.minimum > current)
		{
			statsData.minimum = current;
		}

		//std::max
		if (statsData.maximum < current)
		{
			statsData.maximum = current;
		}

		statsData.accumulatedValue += current;
	}

	void DisplayNumericStatsData(const NumericStatsData& statsData, const char* text) const
	{
		std::cout << "Max " << text << " " << statsData.maximum << std::endl;
		std::cout << "Min " << text << " " << statsData.minimum << std::endl;
		std::cout << "Average " << text << " " << (statsData.accumulatedValue / m_count) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void UpdateAverageWindDirection(const std::optional<double>& current)
	{
		if (current.has_value())
		{
			if (m_avgWindDirection.has_value())
			{
				double mid;
				if ((mid = abs(*current - *m_avgWindDirection)) > 180)
				{
					double average = (*current + *m_avgWindDirection) / 2;
					if (average > 180)
					{
						m_avgWindDirection = average - 180;
					}
					else if (average < 180)
					{
						m_avgWindDirection = average + 180;
					}
					else
					{
						m_avgWindDirection = std::nullopt;
					}
				}
				else if (mid < 180)
				{
					m_avgWindDirection = (*current + *m_avgWindDirection) / 2;
				}
				else
				{
					m_avgWindDirection = std::nullopt;
				}
			}
			else
			{
				m_avgWindDirection = current;
			}
		}
	}

	void DisplayAverageWindDirection()
	{
		if (m_avgWindDirection.has_value())
		{
			std::cout << "Avg wind direction " << *m_avgWindDirection << std::endl;
		}
		else
		{
			std::cout << "Avg wind direction -- calm" << std::endl;
		}
	}

	NumericStatsData m_temperatureStats;
	NumericStatsData m_humidityStats;
	NumericStatsData m_pressureStats;
	NumericStatsData m_windSpeedStats;

	std::optional<double> m_avgWindDirection;

	unsigned m_count = 0;
};
