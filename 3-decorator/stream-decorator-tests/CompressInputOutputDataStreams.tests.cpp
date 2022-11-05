#include <catch.hpp>

#include "FileInputDataStream.h"
#include "FileOutputDataStream.h"
#include "CompressOutputDataStreamDecorator.h"
#include "DecompressInputDataStreamDecorator.h"

TEST_CASE("Compressing and decompressing data through file stream")
{
	// sequence 'aaaaaabbbbbbb' compresses into '6a7b'
	auto data = "aaaaaabbbbbbb";
	size_t size = strlen(data) + 1;

	// Writing compressed data to file
	{
		OutputDataStreamPtr outputStream = std::make_unique<FileOutputDataStream>("compressed.txt");
		OutputDataStreamPtr compressOutputStream = std::make_unique<CompressOutputDataStreamDecorator>(std::move(outputStream));

		compressOutputStream->WriteBlock(data, size);
	}

	// Decompressing data
	{
		InputDataStreamPtr inputStream = std::make_unique<FileInputDataStream>("compressed.txt");
		InputDataStreamPtr decompressInputStream = std::make_unique<DecompressInputDataStreamDecorator>(std::move(inputStream));
		char* decompressedData = new char[size]();

		decompressInputStream->ReadBlock(decompressedData, size);

		REQUIRE(strcmp(decompressedData, data) == 0);

		delete[] decompressedData;
	}
}
