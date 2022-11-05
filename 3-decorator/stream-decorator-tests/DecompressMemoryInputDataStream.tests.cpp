#include <catch.hpp>

#include "DecompressInputDataStreamDecorator.h"
#include "MemoryInputDataStream.h"

TEST_CASE("Invoking IsEOF method of empty stream")
{
	InputDataStreamPtr emptyStream = std::make_unique<MemoryInputDataStream>();

	SECTION("Invoking IsEOF of undecorated stream")
	{
		REQUIRE(emptyStream->IsEOF());
	}

	SECTION("Decorating stream and invoking IsEOF")
	{
		auto decompressEmptyStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(emptyStream));

		REQUIRE(decompressEmptyStream->IsEOF());
	}
}

TEST_CASE("Invoking IsEOF method of filled stream")
{
	InputDataStreamPtr filledStream = std::make_unique<MemoryInputDataStream>(std::vector<uint8_t>({ 0, 1, 2 }));

	SECTION("Invoking IsEOF of undecorated stream")
	{
		REQUIRE(!filledStream->IsEOF());
	}

	SECTION("Decorating stream and invoking IsEOF")
	{
		auto decompressEmptyStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(filledStream));

		REQUIRE(!decompressEmptyStream->IsEOF());
	}
}

TEST_CASE("Reading single byte from empty stream should throw std::ios::failure")
{
	InputDataStreamPtr emptyStream = std::make_unique<MemoryInputDataStream>();
	InputDataStreamPtr decompressStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(emptyStream));

	REQUIRE_THROWS_AS(decompressStream->ReadByte(), std::ios::failure);
}

TEST_CASE("Reading sequence of bytes from compressed input stream")
{
	//            v---v--- symbol codes
	// sequence 2,0,2,1 decompress into 0,0,1,1
	//          ^---^--- length bytes
	InputDataStreamPtr filledStream = std::make_unique<MemoryInputDataStream>(std::vector<uint8_t>({ 2, 0, 2, 1 }));
	InputDataStreamPtr decompressStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(filledStream));

	auto firstByte = decompressStream->ReadByte();
	REQUIRE(firstByte == 0);

	auto secondByte = decompressStream->ReadByte();
	REQUIRE(secondByte == 0);

	auto thirdByte = decompressStream->ReadByte();
	REQUIRE(thirdByte == 1);

	auto fourthByte = decompressStream->ReadByte();
	REQUIRE(fourthByte == 1);

	REQUIRE(decompressStream->IsEOF());
	REQUIRE_THROWS_AS(decompressStream->ReadByte(), std::ios::failure);
}

TEST_CASE("Reading stream with invalid compressed data (length byte equals zero)")
{
	//            v---v--- symbol codes
	// sequence 0,0,2,1 cause std::ios::failure exception
	//          ^---^--- length bytes
	//          ^-- invalid length byte
	InputDataStreamPtr filledStream = std::make_unique<MemoryInputDataStream>(std::vector<uint8_t>({ 0, 0, 2, 1 }));
	InputDataStreamPtr decompressStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(filledStream));

	REQUIRE_THROWS_AS(decompressStream->ReadByte(), std::ios::failure);
}

TEST_CASE("Reading block of bytes from empty stream should read 0 bytes")
{
	InputDataStreamPtr emptyStream = std::make_unique<MemoryInputDataStream>();
	InputDataStreamPtr decompressStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(emptyStream));

	REQUIRE(decompressStream->IsEOF());
	REQUIRE(decompressStream->ReadBlock(new char(0), 1) == 0);
}

TEST_CASE("Reading block of bytes from compressed stream")
{
	//            v---v--- symbol codes
	// sequence 2,0,2,1 decompress into 0,0,1,1
	//          ^---^--- length bytes
	InputDataStreamPtr filledStream = std::make_unique<MemoryInputDataStream>(std::vector<uint8_t>({ 2, 0, 2, 1 }));
	InputDataStreamPtr decompressStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(filledStream));

	SECTION("Reading less bytes than stream has")
	{
		char* data = new char[3]();
		decompressStream->ReadBlock(data, 3);

		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 0);
		REQUIRE(data[2] == 1);

		REQUIRE(!decompressStream->IsEOF());

		delete[] data;
	}

	SECTION("Reading accurately that much bytes as stream contains")
	{
		char* data = new char[4]();
		decompressStream->ReadBlock(data, 4);

		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 0);
		REQUIRE(data[2] == 1);
		REQUIRE(data[3] == 1);

		REQUIRE(decompressStream->IsEOF());

		delete[] data;
	}

	SECTION("Reading more bytes than stream has, should read only 4")
	{
		char* data = new char[5]();

		REQUIRE(decompressStream->ReadBlock(data, 5) == 4);

		delete[] data;
	}
}
