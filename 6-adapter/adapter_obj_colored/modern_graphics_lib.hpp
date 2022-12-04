#pragma once

#include <iostream>
#include <stdexcept>

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
class CPoint
{
public:
	CPoint(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
		if (!IsColorComponentValid(r) || !IsColorComponentValid(g) || !IsColorComponentValid(b) || !IsColorComponentValid(a))
		{
			throw std::invalid_argument("Invalid color component value");
		}
	}
	float r, g, b, a;

private:
	bool IsColorComponentValid(float val)
	{
		if (val < 0.0f || val > 1.0f)
		{
			return false;
		}

		return true;
	}
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream& strm)
		: m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << std::endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << "  <line fromX=\"" << start.x << "\" fromY=\"" << start.y << "\" toX=\"" << end.x << "\" toY=\"" << end.y << "\">\n"
			  << "    <color r=\"" << color.r << "\" g=\"" << color.g << "\" b=\"" << color.b << "\" a=\"" << color.a << "\" />\n"
			  << "  </line>\n";
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << std::endl;
		m_drawing = false;
	}

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib
