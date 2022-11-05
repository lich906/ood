#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>
#include <iostream>

namespace Constants
{
constexpr std::string_view ENCRYPT_OPTION = "--encrypt";
constexpr std::string_view DECRYPT_OPTION = "--decrypt";
constexpr std::string_view DECOMPRESS_OPTION = "--decompress";
constexpr std::string_view COMPRESS_OPTION = "--compress";
constexpr std::string_view OPTIONS_HINT = "Options:\n"
"\t--encrypt <key>\t\tAdds encryption step with key <key> during writing to output file. Option can be used multiple times to execute multiple encryption steps.\n"
"\t--decrypt <key>\t\tAdds decryption step with key <key> during reading from input file. Option can be used multiple times to execute multiple decryption steps.\n"
"\t--compress\t\tAdds compression step during output.\n"
"\t--decompress\t\tAdds decompression step during input.\n";
}

class ProgramArguments
{
public:
	ProgramArguments(int argc, char** argv);

	void Parse();

	void PrintUsageHint();

	std::string GetInputFileName() const;
	std::string GetOutputFileName() const;
	const std::vector<size_t>& GetEncryptionKeys() const;
	const std::vector<size_t>& GetDecryptionKeys() const;
	bool CompressionEnabled() const;
	bool DecompressionEnabled() const;

private:
	void ParseOption(int& order, char* optionStr);

	size_t ParseKeyArgument(char* keyStr);

	int m_argc;
	char** m_argv;

	std::vector<size_t> m_encryptionKeys;
	std::vector<size_t> m_decryptionKeys;
	std::string m_inputFileName;
	std::string m_outputFileName;
	bool m_decompressionEnabled;
	bool m_compressionEnabled;
};

#endif // !PROGRAM_ARGUMENTS_H
