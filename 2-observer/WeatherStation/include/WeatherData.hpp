#pragma once
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#include "CObservable.hpp"
#include "WeatherInfo\WeatherInfoPro.h"
#include "DataType.h"

class WeatherData : 
	public CObservable<DataType::AllPro>, 
	public CObservable<DataType::Temperature>, 
	public CObservable<DataType::Pressure>
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

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	std::optional<double> GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		CObservable<DataType::AllPro>::NotifyObservers();
	}

	void TemperatureChanged()
	{
		CObservable<DataType::Temperature>::NotifyObservers();
	}

	void PressureChanged()
	{
		CObservable<DataType::Pressure>::NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, const std::optional<double>& windDirection)
	{
		m_humidity = humidity;

		if (temp != m_temperature)
		{
			m_temperature = temp;
			TemperatureChanged();
		}

		if (pressure != m_pressure)
		{
			m_pressure = pressure;
			PressureChanged();
		}

		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}

protected:
	DataType::AllPro CObservable<DataType::AllPro>::GetChangedData(const DataType::AllPro*) const override
	{
		WeatherInfoPro info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		info.sourcePtr = this;
		return info;
	}

	DataType::Temperature CObservable<DataType::Temperature>::GetChangedData(const DataType::Temperature*) const override
	{
		return GetTemperature();
	}

	DataType::Pressure CObservable<DataType::Pressure>::GetChangedData(const DataType::Pressure*) const override
	{
		return GetPressure();
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	std::optional<double> m_windDirection = std::nullopt;
};
