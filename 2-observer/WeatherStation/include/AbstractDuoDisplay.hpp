#pragma once
#include <iostream>

#include "IObservable.h"
#include "WeatherInfo.h"

template <class T>
class AbstractDuoDisplay : public IObserver<T>
{
public:
	AbstractDuoDisplay() {}

	AbstractDuoDisplay(const IObservable<T>* insideData, const IObservable<T>* outsideData)
		: m_insideSourcePtr(insideData)
		, m_outsideSourcePtr(outsideData)
	{
	}

	virtual ~AbstractDuoDisplay() {}

protected:
	virtual void DisplayInfo(const WeatherInfo& data) = 0;

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным.

		В данном классе метод Update реализован как шаблонный. Информации о том, с какого датчика
		поступила информация, выводится здесь, а вывод информации о погоде в нужном виде делегируется
		дочерним классам.
	*/
	void Update(const WeatherInfo& data) override
	{
		if (data.sourcePtr == m_insideSourcePtr)
			std::cout << "Info inside:" << std::endl;
		else if (data.sourcePtr == m_outsideSourcePtr)
			std::cout << "Info outside:" << std::endl;

		DisplayInfo(data);
	}

	const IObservable<T>* m_insideSourcePtr = nullptr;
	const IObservable<T>* m_outsideSourcePtr = nullptr;
};