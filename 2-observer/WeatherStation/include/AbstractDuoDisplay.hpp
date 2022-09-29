#pragma once
#include "WeatherInfo.h"

template <class T>
class AbstractDuoDisplay : public IObserver<T>
{
public:
	AbstractDuoDisplay() {}

	AbstractDuoDisplay(IObservable<T>* insideData, IObservable<T>* outsideData)
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
	void Update(const WeatherInfo& data, const IObservable<WeatherInfo>* observablePtr) override
	{
		if (observablePtr == m_insideSourcePtr)
			std::cout << "Info inside:" << std::endl;
		else if (observablePtr == m_outsideSourcePtr)
			std::cout << "Info outside:" << std::endl;

		DisplayInfo(data);
	}

	IObservable<T>* m_insideSourcePtr = nullptr;
	IObservable<T>* m_outsideSourcePtr = nullptr;
};