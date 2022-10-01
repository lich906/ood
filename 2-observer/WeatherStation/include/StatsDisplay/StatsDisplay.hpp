#pragma once
#include <iostream>

#include "..\IObserver.h"
#include "..\WeatherInfo\WeatherInfo.h"
#include "NumericStatsData.h"

class StatsDisplay : public IObserver<WeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(const WeatherInfo& data) override
	{
		UpdateNumericStatsData(data.temperature, m_temperatureStats);
		UpdateNumericStatsData(data.humidity, m_humidityStats);
		UpdateNumericStatsData(data.pressure, m_pressureStats);

		++m_count;

		DisplayNumericStatsData(m_temperatureStats, "Temperature");
		DisplayNumericStatsData(m_humidityStats, "Humidity");
		DisplayNumericStatsData(m_pressureStats, "Pressure");
	}

	void UpdateNumericStatsData(double current, NumericStatsData& statsData)
	{
		statsData.minimum = std::min(statsData.minimum, current);
		statsData.maximum = std::max(statsData.maximum, current);

		statsData.accumulatedValue += current;
	}

	void DisplayNumericStatsData(const NumericStatsData& statsData, const char* text)
	{
		std::cout << "Max " << text << " " << statsData.maximum << std::endl;
		std::cout << "Min " << text << " " << statsData.minimum << std::endl;
		std::cout << "Average " << text << " " << (statsData.accumulatedValue / m_count) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	NumericStatsData m_temperatureStats;
	NumericStatsData m_humidityStats;
	NumericStatsData m_pressureStats;

	unsigned m_count = 0;
};
