#include <chrono>

#include "ProgramArguments.h"
#include "FileInputDataStream.h"
#include "FileOutputDataStream.h"
#include "CompressOutputDataStreamDecorator.h"
#include "DecompressInputDataStreamDecorator.h"
#include "EncryptOutputDataStreamDecorator.h"
#include "DecryptInputDataStreamDecorator.h"

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(std::forward<Component>(component));
}

auto AddEncryptionStep(size_t key)
{
	return [=](OutputDataStreamPtr&& outputStream) {
		return std::make_unique<EncryptOutputDataStreamDecorator>(std::forward<OutputDataStreamPtr>(outputStream), key);
	};
}

auto AddDecryptionStep(size_t key)
{
	return [=](InputDataStreamPtr&& inputStream) {
		return std::make_unique<DecryptInputDataStreamDecorator>(std::forward<InputDataStreamPtr>(inputStream), key);
	};
}

auto AddCompressionStep()
{
	return [](OutputDataStreamPtr&& outputStream) {
		return std::make_unique<CompressOutputDataStreamDecorator>(std::forward<OutputDataStreamPtr>(outputStream));
	};
}

auto AddDecompressionStep()
{
	return [](InputDataStreamPtr&& inputStream) {
		return std::make_unique<DecompressInputDataStreamDecorator>(std::forward<InputDataStreamPtr>(inputStream));
	};
}

int main(int argc, char** argv)
try
{
	ProgramArguments programArguments(argc, argv);

	try
	{
		programArguments.Parse();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		programArguments.PrintUsageHint();

		return 1;
	}

	InputDataStreamPtr inputFile = std::make_unique<FileInputDataStream>(programArguments.GetInputFileName());
	OutputDataStreamPtr outputFile = std::make_unique<FileOutputDataStream>(programArguments.GetOutputFileName());

	for (const auto& decryptionKey : programArguments.GetDecryptionKeys())
	{
		inputFile = std::move(inputFile) << AddDecryptionStep(decryptionKey);
	}

	for (const auto& encryptionKey : programArguments.GetEncryptionKeys())
	{
		outputFile = std::move(outputFile) << AddEncryptionStep(encryptionKey);
	}
	
	if (programArguments.DecompressionEnabled())
	{
		inputFile = std::move(inputFile) << AddDecompressionStep();
	}

	if (programArguments.CompressionEnabled())
	{
		outputFile = std::move(outputFile) << AddCompressionStep();
	}

	auto startTime = std::chrono::steady_clock::now();

	uint8_t* block = new uint8_t[Constants::BUFF_SIZE]();
	std::streamsize readSize = 1;
	while (!inputFile->IsEOF() && readSize)
	{
		readSize = inputFile->ReadBlock(block, Constants::BUFF_SIZE);
		outputFile->WriteBlock(block, readSize);
	}
	delete[] block;

	std::chrono::duration<double> elapsedTime = std::chrono::steady_clock::now() - startTime;
	std::cout << "Done in " << elapsedTime.count() << " s." << std::endl;

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}
