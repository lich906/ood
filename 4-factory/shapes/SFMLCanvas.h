#ifndef SFML_CANVAS_H

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>

#include "ICanvas.h"

class SFMLCanvas : public ICanvas
{
public:
	SFMLCanvas(size_t width, size_t height);

	void SetColor(Color color) override;

	void DrawLine(Point from, Point to) override;

	void DrawEllipse(Point center, size_t width, size_t height) override;

	bool SaveImageToFile(const std::string& fileName);

private:
	sf::RenderTexture m_canvas;
	sf::Color m_currentColor = sf::Color::White;
	std::vector<std::unique_ptr<sf::Drawable>> m_drawBuffer;

	class EllipseShape : public sf::Shape
	{
	public:
		EllipseShape(const Point& center, const sf::Vector2f& radius = sf::Vector2f(0, 0))
			: m_center(center)
			, m_radius(radius)
		{
			update();
		}

		void setRadius(const sf::Vector2f& radius)
		{
			m_radius = radius;
			update();
		}

		const sf::Vector2f& getRadius() const
		{
			return m_radius;
		}

		size_t getPointCount() const override
		{
			return 30;
		}

		sf::Vector2f getPoint(size_t index) const override
		{
			float angle = index * 2 * M_PI / getPointCount() - M_PI / 2;
			float x = std::cos(angle) * m_radius.x;
			float y = std::sin(angle) * m_radius.y;

			return sf::Vector2f(m_radius.x + x + m_center.x, m_radius.y + y + m_center.y);
		}

	private:
		sf::Vector2f m_radius;
		Point m_center;
	};
};

#endif // !SFML_CANVAS_H
