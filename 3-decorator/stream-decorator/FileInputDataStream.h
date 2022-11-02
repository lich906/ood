#ifndef FILE_INPUT_STREAM_H
#define FILE_INPUT_STREAM_H

#include <string>
#include <fstream>
#include "IInputDataStream.h"

class FileInputDataStream : public IInputDataStream
{
public:
	FileInputDataStream() = default;

	FileInputDataStream(const std::string& fileName);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_stream;
};

#endif // !FILE_INPUT_STREAM_H
