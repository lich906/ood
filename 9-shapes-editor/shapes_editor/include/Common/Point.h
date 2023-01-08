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

	bool operator!=(const Point& other) const { return x != other.x || y != other.y; }
	bool operator==(const Point& other) const { return !(*this != other); }

	bool operator>(const Point& other) const { return (x - other.x > 0) && (y - other.y > 0); }
	bool operator<(const Point& other) const { return (x - other.x < 0) || (y - other.y < 0); }

	float x = 0;
	float y = 0;
};

} // namespace common
