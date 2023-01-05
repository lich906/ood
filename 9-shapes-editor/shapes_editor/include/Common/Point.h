#pragma once

namespace common
{

struct Point
{
	Point() = default;

	Point(float x, float y)
		: x(x)
		, y(y)
	{
	}

	bool operator!=(const Point& other) { return x != other.x || y != other.y; }
	bool operator==(const Point& other) { return !(*this != other); }

	float x = 0;
	float y = 0;
};

} // namespace common
