#include "../../include/Model/Shape.h"

Shape::Shape(ShapeType type, int zIndex, std::function<void(std::unique_ptr<Command>&&)> registerCommand)
	: m_type(type)
	, m_id(++lastId)
	, m_zIndex(zIndex)
	, m_registerCommand(std::move(registerCommand))
{
}

size_t Shape::GetId() const
{
	return m_id;
}

ShapeType Shape::GetType() const
{
	return m_type;
}

Point Shape::GetTopLeft() const
{
	return m_topLeft;
}

Point Shape::GetBottomRight() const
{
	return m_bottomRight;
}

void Shape::Resize(const Point& topLeft, const Point& bottomRight)
{
	auto command = std::make_unique<FunctionalCommand>(
		[this, topLeft, bottomRight]() {
			m_topLeft = topLeft;
			m_bottomRight = bottomRight;
		},
		[this, prevTl = m_topLeft, prevBr = m_bottomRight]() {
			m_topLeft = prevTl;
			m_bottomRight = prevBr;
		});

	m_registerCommand(std::move(command));
}

void Shape::Move(float dx, float dy)
{
	auto command = std::make_unique<FunctionalCommand>(
		[this, dx, dy]() {
			m_topLeft.x += dx;
			m_bottomRight.x += dx;
			m_topLeft.y += dy;
			m_bottomRight.y += dy;
		},
		[this, dx, dy]() {
			m_topLeft.x -= dx;
			m_bottomRight.x -= dx;
			m_topLeft.y -= dy;
			m_bottomRight.y -= dy;
		});

	m_registerCommand(std::move(command));
}

Color Shape::GetFillColor() const
{
	return m_fillColor;
}

void Shape::SetFillColor(Color color)
{
	auto command = std::make_unique<FunctionalCommand>(
		[this, color]() {
			m_fillColor = color;
		},
		[this, prevColor = m_fillColor]() {
			m_fillColor = prevColor;
		});

	m_registerCommand(std::move(command));
}

Color Shape::GetBorderColor() const
{
	return m_borderColor;
}

void Shape::SetBorderColor(Color color)
{
	auto command = std::make_unique<FunctionalCommand>(
		[this, color]() {
			m_borderColor = color;
		},
		[this, prevColor = m_borderColor]() {
			m_borderColor = prevColor;
		});

	m_registerCommand(std::move(command));
}

int Shape::GetZIndex() const
{
	return m_zIndex;
}

void Shape::SetZIndex(int zIndex)
{
	auto command = std::make_unique<FunctionalCommand>(
		[this, zIndex]() {
			m_zIndex = zIndex;
		},
		[this, prevZIndex = m_zIndex]() {
			m_zIndex = prevZIndex;
		});

	m_registerCommand(std::move(command));
}
