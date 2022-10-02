#pragma once
#include <iostream>

#include "IObserver.h"
#include "WeatherInfo\WeatherInfoPro.h"
#include "NumericStatsData.h"
#include "WindDirectionUtils.h"

class StatsDisplayPro : public IObserver<WeatherInfoPro>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(const WeatherInfoPro& data) override
	{
		UpdateNumericStatsData(data.temperature, m_temperatureStats);
		UpdateNumericStatsData(data.humidity, m_humidityStats);
		UpdateNumericStatsData(data.pressure, m_pressureStats);
		UpdateNumericStatsData(data.windSpeed, m_windSpeedStats);
		m_avgWindDirection = WindDirectionUtils::UpdateAverageWindDirection(m_avgWindDirection, data.windDirection);

		++m_count;

		DisplayNumericStatsData(m_temperatureStats, "Temperature");
		DisplayNumericStatsData(m_humidityStats, "Humidity");
		DisplayNumericStatsData(m_pressureStats, "Pressure");
		DisplayNumericStatsData(m_windSpeedStats, "Wind Speed");
		std::cout << "Avg Wind direction ";
		WindDirectionUtils::DisplayWindDirection(std::cout, m_avgWindDirection);
		std::cout << std::endl;
	}

	void UpdateNumericStatsData(double current, NumericStatsData& statsData) const
	{
		// std::min
		statsData.minimum = std::min(statsData.minimum, current);

		//std::max
		statsData.maximum = std::max(statsData.maximum, current);

		statsData.accumulatedValue += current;
	}

	void DisplayNumericStatsData(const NumericStatsData& statsData, const char* text) const
	{
		std::cout << "Max " << text << " " << statsData.maximum << std::endl;
		std::cout << "Min " << text << " " << statsData.minimum << std::endl;
		std::cout << "Average " << text << " " << (statsData.accumulatedValue / m_count) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	NumericStatsData m_temperatureStats;
	NumericStatsData m_humidityStats;
	NumericStatsData m_pressureStats;
	NumericStatsData m_windSpeedStats;

	std::optional<double> m_avgWindDirection;

	unsigned m_count = 0;
};