#include "..\..\catch2\catch.hpp"
#include "..\WeatherStation\include\WeatherData.hpp"
#include <sstream>

class MockDisplay : public IObserver<WeatherInfo>
{
public:
	MockDisplay(const int number, std::ostream& output)
		: m_number(number)
		, m_output(output)
	{
	}

private:
	void Update(const WeatherInfo&) override
	{
		m_output << m_number;
	}

	const int m_number;
	std::ostream& m_output;
};

TEST_CASE("Mock displays are notified in correct order")
{
	std::stringstream stringOutput;

	MockDisplay display1(1, stringOutput);
	MockDisplay display2(2, stringOutput);
	MockDisplay display3(3, stringOutput);
	MockDisplay display4(4, stringOutput);

	WeatherData wd;

	wd.RegisterObserver(display3, 2);
	wd.RegisterObserver(display4, -1);
	wd.RegisterObserver(display1, 3);
	wd.RegisterObserver(display2, 2);

	wd.MeasurementsChanged();

	REQUIRE(stringOutput.str() == "1324");

	wd.MeasurementsChanged();

	REQUIRE(stringOutput.str() == "13241324");
}