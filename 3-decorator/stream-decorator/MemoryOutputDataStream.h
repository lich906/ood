#ifndef MEMORY_OUTPUT_DATA_STREAM_H
#define MEMORY_OUTPUT_DATA_STREAM_H

#include <vector>
#include <ios>
#include "IOutputDataStream.h"

class MemoryOutputDataStream : public IOutputDataStream
{
public:
	MemoryOutputDataStream() = default;

	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::vector<uint8_t> m_data;
};

#endif // !MEMORY_OUTPUT_DATA_STREAM_H
