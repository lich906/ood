#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

template <class T>
class DuoDisplay : public IObserver<T>
{
public:
	DuoDisplay() {}

	DuoDisplay(IObservable<T>* insideData, IObservable<T>* outsideData)
		: m_insideSourcePtr(insideData)
		, m_outsideSourcePtr(outsideData)
	{
	}

	virtual ~DuoDisplay() {}

protected:
	virtual void DisplayInfo(const WeatherInfo& data) = 0;

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным.

		В данном классе метод Update реализован как шаблонный. Информации о том, с какого датчика
		поступила информация, выводится здесь, а вывод информации о погоде в нужном виде делегируется
		дочерним классам.
	*/
	void Update(const WeatherInfo& data, const IObservable<WeatherInfo>* observablePtr) override
	{
		if (observablePtr == m_insideSourcePtr)
			std::cout << "Info inside:" << std::endl;
		else if (observablePtr == m_outsideSourcePtr)
			std::cout << "Info outside:" << std::endl;

		DisplayInfo(data);
	}

	IObservable<T>* m_insideSourcePtr = nullptr;
	IObservable<T>* m_outsideSourcePtr = nullptr;
};

class Display : public DuoDisplay<WeatherInfo>
{
public:
	Display() {}

	Display(IObservable<WeatherInfo>* insideData, IObservable<WeatherInfo>* outsideData)
		: DuoDisplay(insideData, outsideData)
	{
	}

private:
	void DisplayInfo(const WeatherInfo& data) override
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

class StatsDisplay : public DuoDisplay<WeatherInfo>
{
public:
	StatsDisplay()
	{
	}

	StatsDisplay(IObservable<WeatherInfo>* insideData, IObservable<WeatherInfo>* outsideData)
		: DuoDisplay(insideData, outsideData)
	{
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void DisplayInfo(const WeatherInfo& data) override
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
		if (statsData.minimum > current)
		{
			statsData.minimum = current;
		}

		if (statsData.maximum < current)
		{
			statsData.maximum = current;
		}

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

class WeatherData : public CObservable<WeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
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
	WeatherInfo GetChangedData() const override
	{
		WeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
