#pragma once

#include "IBeverage.h"
#include "PortionCount.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
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
	CCappuccino() 
		:CCoffee("Cappuccino") 
	{}

	double GetCost() const override 
	{
		return 80; 
	}
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
			break;
		}
	}

private:
	PortionCount m_portionCount;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea() 
		:CBeverage("Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 80; 
	}
};
