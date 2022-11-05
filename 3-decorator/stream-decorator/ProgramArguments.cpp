#include "ProgramArguments.h"

ProgramArguments::ProgramArguments(int argc, char** argv)
	: m_argc(argc)
	, m_argv(argv)
	, m_compressionEnabled(false)
	, m_decompressionEnabled(false)
{
}

void ProgramArguments::Parse()
{
	if (m_argc < 3)
	{
		throw std::runtime_error("Too few arguments.");
	}

	m_inputFileName = m_argv[m_argc - 2];
	m_outputFileName = m_argv[m_argc - 1];

	for (int i = 1; i < m_argc - 2; ++i)
	{
		ParseOption(i, m_argv[i]);
	}
}

void ProgramArguments::PrintUsageHint()
{
	std::cout << "Usage: " + std::string(m_argv[0]) + " [OPTIONS]... INPUT_FILE OUTPUT_FILE" << std::endl
			  << Constants::OPTIONS_HINT << std::endl;
}

std::string ProgramArguments::GetInputFileName() const
{
	return m_inputFileName;
}

std::string ProgramArguments::GetOutputFileName() const
{
	return m_outputFileName;
}

const std::vector<size_t>& ProgramArguments::GetEncryptionKeys() const
{
	return m_encryptionKeys;
}

const std::vector<size_t>& ProgramArguments::GetDecryptionKeys() const
{
	return m_decryptionKeys;
}

bool ProgramArguments::CompressionEnabled() const
{
	return m_compressionEnabled;
}

bool ProgramArguments::DecompressionEnabled() const
{
	return m_decompressionEnabled;
}

void ProgramArguments::ParseOption(int& order, char* optionStr)
{
	if (optionStr == Constants::COMPRESS_OPTION)
	{
		m_compressionEnabled = true;
	}
	else if (optionStr == Constants::DECOMPRESS_OPTION)
	{
		m_decompressionEnabled = true;
	}
	else if (optionStr == Constants::DECRYPT_OPTION)
	{
		auto key = ParseKeyArgument(m_argv[order + 1]);
		m_decryptionKeys.push_back(key);
		++order;
	}
	else if (optionStr == Constants::ENCRYPT_OPTION)
	{
		auto key = ParseKeyArgument(m_argv[order + 1]);
		m_encryptionKeys.push_back(key);
		++order;
	}
	else
	{
		throw std::runtime_error("Unknown option: " + std::string(optionStr));
	}
}

size_t ProgramArguments::ParseKeyArgument(char* keyStr)
{
	try
	{
		return std::stoull(keyStr);
	}
	catch (const std::invalid_argument&)
	{
		throw std::runtime_error("Unable to convert (en/de)cryption key: " + std::string(keyStr));
	}
	catch (const std::out_of_range&)
	{
		throw std::runtime_error("(En/De)cryption key value out of range: " + std::string(keyStr));
	}
}
