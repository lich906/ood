#include "Color.h"

std::istream& operator>>(std::istream& stream, Color& color)
{
	std::string str;
	stream >> str;

	if (str == ColorString::Green)
	{
		color = Color::Green;
	}
	else if (str == ColorString::Red)
	{
		color = Color::Red;
	}
	else if (str == ColorString::Blue)
	{
		color = Color::Blue;
	}
	else if (str == ColorString::Yellow)
	{
		color = Color::Yellow;
	}
	else if (str == ColorString::Pink)
	{
		color = Color::Pink;
	}
	else if (str == ColorString::Black)
	{
		color = Color::Black;
	}
	else
	{
		stream.setstate(std::ios::failbit);
	}

	return stream;
}