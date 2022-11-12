#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string_view>
#include <string>

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black,
};

namespace ColorString
{
constexpr std::string_view Green = "green";
constexpr std::string_view Red = "red";
constexpr std::string_view Blue = "blue";
constexpr std::string_view Yellow = "yellow";
constexpr std::string_view Pink = "pink";
constexpr std::string_view Black = "black";
}; // namespace ColorString

std::istream& operator>>(std::istream& stream, Color& color);

#endif // !COLOR_H
