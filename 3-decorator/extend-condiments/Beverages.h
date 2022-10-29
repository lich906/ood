#pragma once

#include <stdexcept>

#include "IBeverage.h"
#include "PortionCount.h"
#include "PortionSize.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	// убран спецификатор final
	std::string GetDescription() const override
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(PortionCount portionCount)
		: m_portionCount(portionCount)
		, CCoffee("Cappuccino")
	{}

	double GetCost() const override
	{
		switch (m_portionCount)
		{
		case PortionCount::Single:
			return 80;
		case PortionCount::Double:
			return 120;
		default:
			break;
		}
	}

private:
	PortionCount m_portionCount;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(PortionCount portionCount)
		: m_portionCount(portionCount)
		, CCoffee("Latte")
	{}

	double GetCost() const override
	{
		switch (m_portionCount)
		{
		case PortionCount::Single:
			return 90;
		case PortionCount::Double:
			return 130;
		default:
			throw std::invalid_argument("Unkown portion count");
		}
	}

private:
	PortionCount m_portionCount;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& teaSort)
		: m_teaSort(teaSort)
		, CBeverage("Tea")
	{}

	double GetCost() const override
	{
		return 30;
	}

	std::string GetDescription() const override
	{
		return m_teaSort + " " + CBeverage::GetDescription();
	}

private:
	std::string m_teaSort;
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(PortionSize portionSize)
		: CBeverage("Milkshake")
		, m_portionSize(portionSize)
	{}

	double GetCost() const override 
	{
		switch (m_portionSize)
		{
		case PortionSize::Small:
			return 50;
		case PortionSize::Medium:
			return 60;
		case PortionSize::Large:
			return 80;
		default:
			throw std::invalid_argument("Unknown portion size");
		}
	}

private:
	PortionSize m_portionSize;
};
