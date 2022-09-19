#include "..\..\catch2\catch.hpp"
#include "..\WeatherStation\WeatherData.h"

class MockDisplay : public IObserver<WeatherInfo>
{
public:
	MockDisplay(CObservable<WeatherInfo>& observableRef)
		: m_observableRef(observableRef)
	{
	}

private:
	void RemoveSelfFromObservers()
	{
		m_observableRef.RemoveObserver(*this);
	}

	void Update(const WeatherInfo& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;

		RemoveSelfFromObservers();
	}

	CObservable<WeatherInfo>& m_observableRef;
};

TEST_CASE("Invoke RemoveObserver in observer's Update method")
{
	WeatherData wd;

	MockDisplay mockDisplay(wd);
	wd.RegisterObserver(mockDisplay);

	REQUIRE_THROWS_AS(wd.SetMeasurements(3, 0.7, 760), std::logic_error);

	REQUIRE_NOTHROW(wd.RemoveObserver(mockDisplay));

	Display display;
	wd.RegisterObserver(display);

	REQUIRE_NOTHROW(wd.SetMeasurements(3, 0.7, 760));
}
