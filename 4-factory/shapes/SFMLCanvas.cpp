#include "SfmlCanvas.h"

SFMLCanvas::SFMLCanvas(size_t width, size_t height)
{
	m_canvas.create(width, height);
}

void SFMLCanvas::SetColor(Color color)
{
	switch (color)
	{
	case Color::Green:
		m_currentColor = sf::Color::Green;
		break;
	case Color::Red:
		m_currentColor = sf::Color::Red;
		break;
	case Color::Blue:
		m_currentColor = sf::Color::Blue;
		break;
	case Color::Yellow:
		m_currentColor = sf::Color::Yellow;
		break;
	case Color::Pink:
		m_currentColor = sf::Color::Magenta;
		break;
	case Color::Black:
		m_currentColor = sf::Color::Black;
		break;
	default:
		break;
	}
}

void SFMLCanvas::DrawLine(Point from, Point to)
{
	auto line = std::make_unique<sf::VertexArray>(sf::Lines, 2);

	(*line)[0].position = sf::Vector2f(from.x, from.y);
	(*line)[0].color = m_currentColor;
	(*line)[1].position = sf::Vector2f(to.x, to.y);
	(*line)[1].color = m_currentColor;

	m_drawBuffer.emplace_back(std::move(line));
}

void SFMLCanvas::DrawEllipse(Point center, size_t width, size_t height)
{
	auto ellipse = std::make_unique<EllipseShape>(center, sf::Vector2f(width, height));
	ellipse->setOutlineColor(m_currentColor);
	ellipse->setOutlineThickness(1.0);
	ellipse->setFillColor(sf::Color::Transparent);

	m_drawBuffer.emplace_back(std::move(ellipse));
}

bool SFMLCanvas::SaveImageToFile(const std::string& fileName)
{
	for (const auto& drawable : m_drawBuffer)
	{
		m_canvas.draw(*drawable);
	}

	m_canvas.display();

	auto image = m_canvas.getTexture().copyToImage();

	return image.saveToFile(fileName);
}
