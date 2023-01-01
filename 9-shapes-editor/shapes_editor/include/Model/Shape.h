#pragma once

#include <type_traits>
#include <functional>

#include "IShape.h"
#include "Defaults.h"
#include "Command/FunctionalCommand.h"

class Shape : public IShape
{
public:
	Shape(ShapeType type, int zIndex, std::function<void(std::unique_ptr<Command>&&)> registerCommand);

	ShapeId GetId() const override;

	ShapeType GetType() const override;

	Point GetTopLeft() const override;
	Point GetBottomRight() const override;

	void Resize(const Point& topLeft, const Point& bottomRight) override;
	void Move(float dx, float dy) override;

	Color GetFillColor() const override;
	void SetFillColor(Color color) override;

	Color GetBorderColor() const override;
	void SetBorderColor(Color color) override;

	int GetZIndex() const;
	void SetZIndex(int zIndex);

private:
	ShapeType m_type;
	ShapeId m_id;
	Point m_topLeft = Defaults::TopLeftPoint;
	Point m_bottomRight = Defaults::BottomRightPoint;
	Color m_fillColor = Defaults::FillColor;
	Color m_borderColor = Defaults::BorderColor;
	int m_zIndex;

	std::function<void(std::unique_ptr<Command>&&)> m_registerCommand;

	inline static ShapeId lastId = 0;
};
