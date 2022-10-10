#pragma once
#include <iostream>

#include "IObservable.h"
#include "WeatherInfo\WeatherInfoPro.h"

// ����������� ������� ���������
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
	virtual void DisplayInfo(const T& data) = 0;

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������.

		� ������ ������ ����� Update ���������� ��� ���������. ���������� � ���, � ������ �������
		��������� ����������, ��������� �����, � ����� ���������� � ������ � ������ ���� ������������
		�������� �������.
	*/
	void Update(const T& data) override
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

// ����������� ���������
template <class TInside, class TOutside>
class AbstractDuoDisplayPro : public IObserver<TInside>, public IObserver<TOutside>
{
public:
	AbstractDuoDisplayPro() {}

	AbstractDuoDisplayPro(const IObservable<TInside>* insideData, const IObservable<TOutside>* outsideData)
		: m_insideSourcePtr(insideData)
		, m_outsideSourcePtr(outsideData)
	{
	}

	virtual ~AbstractDuoDisplayPro() {}

protected:
	virtual void DisplayInfoInside(const TInside& data) = 0;
	virtual void DisplayInfoOutside(const TOutside& data) = 0;

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������.

		� ������ ������ ����� Update ���������� ��� ���������. ���������� � ���, � ������ �������
		��������� ����������, ��������� �����, � ����� ���������� � ������ � ������ ���� ������������
		�������� �������.
	*/
	void Update(const TInside& data) override
	{
		DisplaySourceLocation(data.sourcePtr);

		DisplayInfoInside(data);
	}

	void Update(const TOutside& data) override
	{
		DisplaySourceLocation(data.sourcePtr);

		DisplayInfoOutside(data);
	}

	void DisplaySourceLocation(const void* sourcePtr)
	{
		if (sourcePtr == m_insideSourcePtr)
			std::cout << "Info inside:" << std::endl;
		else if (sourcePtr == m_outsideSourcePtr)
			std::cout << "Info outside:" << std::endl;
	}

	const IObservable<TInside>* m_insideSourcePtr = nullptr;
	const IObservable<TOutside>* m_outsideSourcePtr = nullptr;
};