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
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������.

		� ������ ������ ����� Update ���������� ��� ���������. ���������� � ���, � ������ �������
		��������� ����������, ��������� �����, � ����� ���������� � ������ � ������ ���� ������������
		�������� �������.
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