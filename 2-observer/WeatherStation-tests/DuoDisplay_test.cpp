#include "..\..\catch2\catch.hpp"
#include "..\WeatherStation\WeatherData.h"
#include <sstream>

class MockDuoDisplay : public DuoDisplay<WeatherInfo>
{
public:
	MockDuoDisplay(IObservable<WeatherInfo>* insideData, IObservable<WeatherInfo>* outsideData)
		: DuoDisplay(insideData, outsideData)
	{
	}

private:
	void DisplayInfo(const WeatherInfo&) override {}
};

TEST_CASE("Display info from two data sources")
{
	WeatherData wdInside, wdOutside, wdOther;

	MockDuoDisplay mock(&wdInside, &wdOutside);

	std::ostringstream oss;
	std::streambuf* coutStreambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	SECTION("Inside data and outside data changed")
	{
		wdInside.RegisterObserver(mock);
		wdOutside.RegisterObserver(mock);

		wdInside.MeasurementsChanged();
		wdInside.MeasurementsChanged();
		wdOutside.MeasurementsChanged();

		REQUIRE(oss.str() == "Info inside:\nInfo inside:\nInfo outside:\n");
	}

	SECTION("Weather data that not registered in mock object as inside or outside")
	{
		wdOther.RegisterObserver(mock);

		REQUIRE(oss.str() == "");
	}

	std::cout.rdbuf(coutStreambuf);
}
