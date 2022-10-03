#pragma once
#include <iostream>

#include "IObserver.h"
#include "DataType.h"

class SimpleDisplay : public IObserver<DataType::Temperature>, public IObserver<DataType::Pressure>
{
private:
	void Update(const DataType::Temperature& data) override
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "\tCurrent Temp " << data << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}

	void Update(const DataType::Pressure& data) override
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "\tCurrent Pressure " << data << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}
};