#include "../../include/Model/Shape.h"

using namespace model;

Shape::Shape(ShapeType type, int zIndex, std::function<void(std::unique_ptr<Command>&&)> registerCommand)
	: m_type(type)
	, m_id(++lastId)
	, m_zIndex(zIndex)
	, m_registerCommand(std::move(registerCommand))
{
}

ShapeId Shape::GetId() const
{
	return m_id;
}

ShapeType Shape::GetType() const
{
	return m_type;
}

common::Point Shape::GetTopLeft() const
{
	return m_topLeft;
}

common::Point Shape::GetBottomRight() const
{
	return m_bottomRight;
}

void Shape::Resize(const common::Point& topLeft, const common::Point& bottomRight)
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

common::Color Shape::GetFillColor() const
{
	return m_fillColor;
}

void Shape::SetFillColor(const common::Color& color)
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

common::Color Shape::GetBorderColor() const
{
	return m_borderColor;
}

void Shape::SetBorderColor(const common::Color& color)
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
	if ((zIndex - m_zIndex) > 1)
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
}
