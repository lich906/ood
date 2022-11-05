#include <catch.hpp>

#include "MemoryOutputDataStream.h"

TEST_CASE("Writing data to memory stream")
{
	auto outputStream = std::make_unique<MemoryOutputDataStream>();

	SECTION("Writing data to memory stream")
	{
		REQUIRE_NOTHROW(outputStream->WriteByte(-1));
		REQUIRE_NOTHROW(outputStream->WriteByte(0));
		REQUIRE_NOTHROW(outputStream->WriteByte(256));
	}

	SECTION("Writing data blocks to stream")
	{
		REQUIRE_NOTHROW(outputStream->WriteBlock("data", 4));
	}

	SECTION("Passing nullptr instead of data, should cause exception")
	{
		REQUIRE_THROWS_AS(outputStream->WriteBlock(nullptr, 5), std::invalid_argument);
	}
}

