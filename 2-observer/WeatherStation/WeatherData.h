﻿#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	const IObservable<WeatherInfo>* sourcePtr = nullptr;
};

class Display: public IObserver<WeatherInfo>
{
protected:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(const WeatherInfo& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
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
protected:
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

private:
	void UpdateNumericStatsData(double current, NumericStatsData& statsData)
	{
		// std::min
		statsData.minimum = std::min(statsData.minimum, current);

		//std::max
		statsData.maximum = std::min(statsData.maximum, current);

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

class DuoDisplay : public Display
{
public:
	DuoDisplay(const IObservable<WeatherInfo>* insideSourcePtr, const IObservable<WeatherInfo>* outsideSourcePtr)
		: m_insideSourcePtr(insideSourcePtr)
		, m_outsideSourcePtr(outsideSourcePtr)
	{
	}

protected:
	void ShowSourceInfo(const IObservable<WeatherInfo>* sourcePtr)
	{
		if (sourcePtr == m_insideSourcePtr)
		{
			std::cout << "Info inside:";
		}
		else if (sourcePtr == m_outsideSourcePtr)
		{
			std::cout << "Info outside:";
		}

		std::cout << std::endl;
	}

private:
	void Update(const WeatherInfo& data) override
	{
		ShowSourceInfo(data.sourcePtr);

		Display::Update(data);
	}

	const IObservable<WeatherInfo>* m_insideSourcePtr;
	const IObservable<WeatherInfo>* m_outsideSourcePtr;
};

class DuoStatsDisplay : public StatsDisplay
{
public:
	DuoStatsDisplay(const IObservable<WeatherInfo>* insideSourcePtr, const IObservable<WeatherInfo>* outsideSourcePtr)
		: m_insideSourcePtr(insideSourcePtr)
		, m_outsideSourcePtr(outsideSourcePtr)
	{
	}

protected:
	void ShowSourceInfo(const IObservable<WeatherInfo>* sourcePtr)
	{
		if (sourcePtr == m_insideSourcePtr)
		{
			std::cout << "Info inside:";
		}
		else if (sourcePtr == m_outsideSourcePtr)
		{
			std::cout << "Info outside:";
		}

		std::cout << std::endl;
	}

private:
	void Update(const WeatherInfo& data) override
	{
		ShowSourceInfo(data.sourcePtr);

		StatsDisplay::Update(data);
	}

	const IObservable<WeatherInfo>* m_insideSourcePtr;
	const IObservable<WeatherInfo>* m_outsideSourcePtr;
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	WeatherInfo GetChangedData()const override
	{
		WeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.sourcePtr = this;
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
