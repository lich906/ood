#pragma once

#include <type_traits>
#include <functional>

#include "IShape.h"
#include "constants.h"
#include "Command/FunctionalCommand.h"

namespace model
{

class Shape : public IShape
{
public:
	Shape(ShapeType type, int zIndex, std::function<void(std::unique_ptr<Command>&&)> registerCommand);

	ShapeId GetId() const override;

	ShapeType GetType() const override;

	common::Point GetTopLeft() const override;
	common::Point GetBottomRight() const override;

	void Resize(const common::Point& topLeft, const common::Point& bottomRight) override;

	common::Color GetFillColor() const override;
	void SetFillColor(const common::Color& color) override;

	common::Color GetBorderColor() const override;
	void SetBorderColor(const common::Color& color) override;

	int GetZIndex() const;
	void SetZIndex(int zIndex);

private:
	ShapeType m_type;
	ShapeId m_id;
	common::Point m_topLeft = model::constants::TopLeftPoint;
	common::Point m_bottomRight = model::constants::BottomRightPoint;
	common::Color m_fillColor = model::constants::FillColor;
	common::Color m_borderColor = model::constants::BorderColor;
	int m_zIndex;

	std::function<void(std::unique_ptr<Command>&&)> m_registerCommand;

	inline static ShapeId lastId = 0;
};

} // namespace model
