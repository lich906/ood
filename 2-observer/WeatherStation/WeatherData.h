#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <optional>
#include "Observer.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	std::optional<double> windDirection;
};

class Display: public IObserver<WeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(const WeatherInfo& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		DisplayWindDirection(data.windDirection);
		std::cout << "----------------" << std::endl;
	}

	void DisplayWindDirection(const std::optional<double>& windDirection)
	{
		if (windDirection.has_value())
		{
			std::cout << "Current Wind Direction " << *windDirection;
		}
		else
		{
			std::cout << "Current Wind Direction -- calm";
		}

		std::cout << std::endl;
	}
};

struct NumericStatsData
{
	double minimum = std::numeric_limits<double>::infinity();
	double maximum = -std::numeric_limits<double>::infinity();
	double accumulatedValue = 0;
};

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

class WeatherData : public CObservable<WeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	double GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	WeatherInfo GetChangedData()const override
	{
		WeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0.0;
};
