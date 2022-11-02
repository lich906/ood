#ifndef MEMORY_INPUT_DATA_STREAM_H
#define MEMORY_INPUT_DATA_STREAM_H

#include <vector>
#include "IInputDataStream.h"

class MemoryInputDataStream : public IInputDataStream
{
public:
	MemoryInputDataStream() = default;

	MemoryInputDataStream(std::vector<uint8_t> data);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t> m_data;
	size_t m_cursorPos;
};

#endif // !MEMORY_INPUT_DATA_STREAM_H
