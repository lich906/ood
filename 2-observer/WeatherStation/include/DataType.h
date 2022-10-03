#pragma once
#include <optional>

#include "WeatherInfo/WeatherInfoPro.h"

namespace DataType
{
template <typename T, typename Tag>
class TypeWrapper
{
public:
	TypeWrapper()
		: m_val(T())
	{
	}

	TypeWrapper(const T& val)
		: m_val(val)
	{
	}

	TypeWrapper(T&& val)
		: m_val(val)
	{
	}

	operator T() const { return m_val; }

private:
	T m_val;
};

using Temperature = TypeWrapper<double, struct TempTag>;
using Humidity = TypeWrapper<double, struct HumidTag>;
using Pressure = TypeWrapper<double, struct PressTag>;
using WindSpeed = TypeWrapper<double, struct WindSpeedTag>;
using WindDirection = TypeWrapper<std::optional<double>, struct WindDirTag>;

using All = WeatherInfo;
using AllPro = WeatherInfoPro;
}
