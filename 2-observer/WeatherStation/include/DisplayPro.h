#pragma once
#include <iostream>

#include "WeatherInfoPro.h"
#include "IObserver.h"

class Display : public IObserver<WeatherInfoPro>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(const WeatherInfoPro& data) override
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
