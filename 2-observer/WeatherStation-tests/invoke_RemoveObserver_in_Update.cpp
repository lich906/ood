#include "..\..\catch2\catch.hpp"
#include "..\WeatherStation\WeatherData.h"
#include <sstream>

class MockDisplay : public IObserver<WeatherInfo>
{
public:
	MockDisplay(CObservable<WeatherInfo>& observableRef, std::ostream& output)
		: m_observableRef(observableRef)
		, m_output(output)
	{
	}

private:
	void RemoveSelfFromObservers()
	{
		m_observableRef.RemoveObserver(*this);
		m_output << "removed";
	}

	void Update(const WeatherInfo& data) override
	{
		RemoveSelfFromObservers();
	}

	CObservable<WeatherInfo>& m_observableRef;
	std::ostream& m_output;
};

TEST_CASE("Invoke RemoveObserver in observer's Update method")
{
	WeatherData wd;
	std::ostringstream oss;

	SECTION("Single observer removes itself in Update() method")
	{
		MockDisplay mock(wd, oss);
		wd.RegisterObserver(mock);

		wd.MeasurementsChanged(); // single observer removed, string "removed" has been written to oss

		wd.MeasurementsChanged(); // no observers left to notify

		REQUIRE(oss.str() == "removed");
	}

	SECTION("Two observers removes themselves in Update() method")
	{
		MockDisplay mock(wd, oss);
		MockDisplay mock2(wd, oss);

		wd.RegisterObserver(mock);
		wd.RegisterObserver(mock2);

		wd.MeasurementsChanged(); // all observers removed, string "removed" has been written to oss twice

		wd.MeasurementsChanged(); // no observers left to notify

		REQUIRE(oss.str() == "removedremoved");
	}
}
