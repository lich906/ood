#include "..\..\catch2\catch.hpp"
#include "..\WeatherStation\WeatherData.h"
#include <sstream>

class MockDuoDisplay : public DuoDisplay
{
public:
	MockDuoDisplay(const IObservable<WeatherInfo>* insideSourcePtr, const IObservable<WeatherInfo>* outsideSourcePtr)
		: DuoDisplay(insideSourcePtr, outsideSourcePtr)
	{}

private:
	void Update(const WeatherInfo& data) override
	{
		ShowSourceInfo(data.sourcePtr);
	}
};

class MockDuoStatsDisplay : public DuoStatsDisplay
{
public:
	MockDuoStatsDisplay(const IObservable<WeatherInfo>* insideSourcePtr, const IObservable<WeatherInfo>* outsideSourcePtr)
		: DuoStatsDisplay(insideSourcePtr, outsideSourcePtr)
	{
	}

private:
	void Update(const WeatherInfo& data) override
	{
		ShowSourceInfo(data.sourcePtr);
	}
};

TEST_CASE("Duo display show info from two different data sources")
{
	std::ostringstream oss;
	WeatherData inside;
	WeatherData outside;

	MockDuoDisplay sut(&inside, &outside);

	inside.RegisterObserver(sut);
	outside.RegisterObserver(sut);

	
	std::streambuf* coutStreambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	SECTION("Inner data source changed before outer one")
	{
		inside.MeasurementsChanged();
		outside.MeasurementsChanged();

		REQUIRE(oss.str() == "Info inside:\nInfo outside:\n");
	}

	SECTION("Outer data source changed before inner one")
	{
		outside.MeasurementsChanged();
		inside.MeasurementsChanged();

		REQUIRE(oss.str() == "Info outside:\nInfo inside:\n");
	}

	std::cout.rdbuf(coutStreambuf);
}

TEST_CASE("Duo stats display show info from two different data sources")
{
	std::ostringstream oss;
	WeatherData inside;
	WeatherData outside;

	MockDuoStatsDisplay sut(&inside, &outside);

	inside.RegisterObserver(sut);
	outside.RegisterObserver(sut);

	std::streambuf* coutStreambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	SECTION("Inner data source changed before outer one")
	{
		inside.MeasurementsChanged();
		outside.MeasurementsChanged();

		REQUIRE(oss.str() == "Info inside:\nInfo outside:\n");
	}

	SECTION("Outer data source changed before inner one")
	{
		outside.MeasurementsChanged();
		inside.MeasurementsChanged();

		REQUIRE(oss.str() == "Info outside:\nInfo inside:\n");
	}

	std::cout.rdbuf(coutStreambuf);
}