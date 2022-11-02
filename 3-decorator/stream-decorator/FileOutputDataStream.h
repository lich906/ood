#ifndef FILE_OUTPUT_DATA_STREAM_H
#define FILE_OUTPUT_DATA_STREAM_H

#include <string>
#include <fstream>
#include "IOutputDataStream.h"

class FileOutputDataStream : public IOutputDataStream
{
public:
	FileOutputDataStream() = default;

	FileOutputDataStream(const std::string& fileName);

	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_stream;
};

#endif // !FILE_OUTPUT_DATA_STREAM_H
