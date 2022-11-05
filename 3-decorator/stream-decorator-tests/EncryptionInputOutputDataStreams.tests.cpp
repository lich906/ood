#include <catch.hpp>

#include <iostream>

#include "EncryptOutputDataStreamDecorator.h"
#include "DecryptInputDataStreamDecorator.h"
#include "FileInputDataStream.h"
#include "FileOutputDataStream.h"

TEST_CASE("Encrypting and decrypting 0 bytes")
{
	{
		// create empty file
		OutputDataStreamPtr outputStream = std::make_unique<FileOutputDataStream>("empty.txt");
		OutputDataStreamPtr encryptOutputStream = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(outputStream), 0);

		encryptOutputStream->WriteBlock("", 0);
	}

	{
		InputDataStreamPtr inputStream = std::make_unique<FileInputDataStream>("empty.txt");
		InputDataStreamPtr decryptInputStream = std::make_unique<DecryptInputDataStreamDecorator>(std::move(inputStream), 0);
		char* decryptedMessage = new char[2]();

		REQUIRE(decryptInputStream->ReadBlock(decryptedMessage, 2) == 0);

		delete[] decryptedMessage;
	}
}

TEST_CASE("Encrypting and decrypting message through file stream")
{
	size_t key = 1337;
	auto message = "lol kek";
	size_t msgLength = strlen(message) + 1;

	{
		OutputDataStreamPtr outputStream = std::make_unique<FileOutputDataStream>("test1.txt");
		OutputDataStreamPtr encryptOutputStream = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(outputStream), key);

		encryptOutputStream->WriteBlock(message, msgLength);
	}

	{
		InputDataStreamPtr inputStream = std::make_unique<FileInputDataStream>("test1.txt");
		InputDataStreamPtr decryptInputStream = std::make_unique<DecryptInputDataStreamDecorator>(std::move(inputStream), key);
		char* decryptedMessage = new char[msgLength]();

		decryptInputStream->ReadBlock(decryptedMessage, msgLength);

		REQUIRE(strcmp(decryptedMessage, message) == 0);

		delete[] decryptedMessage;
	}
}

TEST_CASE("Encrypting and decrypting with sequence of keys")
{
	size_t keys[] = { 23, 14, 56, 176 };
	auto message = "lol kek 4ebur3k";
	size_t msgLength = strlen(message) + 1;

	// Encrypting message
	{
		OutputDataStreamPtr outputStream = std::make_unique<FileOutputDataStream>("test2.txt");
		OutputDataStreamPtr encryptOutputStream0 = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(outputStream), keys[0]);
		OutputDataStreamPtr encryptOutputStream1 = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(encryptOutputStream0), keys[1]);
		OutputDataStreamPtr encryptOutputStream2 = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(encryptOutputStream1), keys[2]);
		OutputDataStreamPtr encryptOutputStream = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(encryptOutputStream2), keys[3]);

		encryptOutputStream->WriteBlock(message, msgLength);
	}

	// Decrypting message
	{
		InputDataStreamPtr inputStream = std::make_unique<FileInputDataStream>("test2.txt");
		InputDataStreamPtr decryptInputStream0 = std::make_unique<DecryptInputDataStreamDecorator>(std::move(inputStream), keys[0]);
		InputDataStreamPtr decryptInputStream1 = std::make_unique<DecryptInputDataStreamDecorator>(std::move(decryptInputStream0), keys[1]);
		InputDataStreamPtr decryptInputStream2 = std::make_unique<DecryptInputDataStreamDecorator>(std::move(decryptInputStream1), keys[2]);
		InputDataStreamPtr decryptInputStream = std::make_unique<DecryptInputDataStreamDecorator>(std::move(decryptInputStream2), keys[3]);
		char* decryptedMessage = new char[msgLength]();

		decryptInputStream->ReadBlock(decryptedMessage, msgLength);

		REQUIRE(strcmp(decryptedMessage, message) == 0);

		delete[] decryptedMessage;
	}
}
