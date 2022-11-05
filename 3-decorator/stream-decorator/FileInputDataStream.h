#ifndef FILE_INPUT_STREAM_H
#define FILE_INPUT_STREAM_H

#include <string>
#include <fstream>
#include "IInputDataStream.h"

class FileInputDataStream : public IInputDataStream
{
public:
	FileInputDataStream(const std::string& fileName);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	void DetermineFileSize();

	mutable std::ifstream m_stream;
	std::streampos m_fileSize;
};

#endif // !FILE_INPUT_STREAM_H
