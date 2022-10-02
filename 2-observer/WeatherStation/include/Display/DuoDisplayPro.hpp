#pragma once
#include <iostream>

#include "AbstractDuoDisplay.hpp"
#include "WeatherInfo\WeatherInfoPro.h"
#include "WindDirectionUtils.h"

class DuoDisplayPro : public AbstractDuoDisplayPro<WeatherInfo, WeatherInfoPro>
{
private:
	/*
	* Перегрузка абстрактного метода из AbstractDuoDisplayPro, который вызывается в IObserver::Update()
	*/
	void DisplayInfoInside(const WeatherInfo& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	/*
	* Перегрузка абстрактного метода из AbstractDuoDisplayPro, который вызывается в IObserver::Update()
	*/
	void DisplayInfoOutside(const WeatherInfoPro& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction ";
		WindDirectionUtils::DisplayWindDirection(std::cout, data.windDirection);
		std::cout << std::endl;
		std::cout << "----------------" << std::endl;
	}
};
