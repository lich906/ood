#pragma once

#include <stdint.h>

namespace common
{

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	bool operator!=(const Color& other) const
	{
		return r != other.r || g != other.g || b != other.b || a != other.a;
	}
};

} // namespace common
