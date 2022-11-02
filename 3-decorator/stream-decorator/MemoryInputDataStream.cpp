#include "MemoryInputDataStream.h"

MemoryInputDataStream::MemoryInputDataStream(std::vector<uint8_t> data)
	: m_data(std::move(data))
	, m_cursorPos(0)
{
}

bool MemoryInputDataStream::IsEOF() const
{
	return m_cursorPos == m_data.size();
}

uint8_t MemoryInputDataStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios::failure("Unable to read byte: Stream is empty");
	}

	return m_data[m_cursorPos++];
}

std::streamsize MemoryInputDataStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (dstBuffer == nullptr)
	{
		throw std::invalid_argument("Destionation buffer pointer is nullptr");
	}

	if (IsEOF())
	{
		throw std::ios::failure("Unable to read block: Stream is empty");
	}

	size_t readSize = std::min(static_cast<size_t>(size), m_data.size() - m_cursorPos);
	std::memcpy(dstBuffer, m_data.data() + m_cursorPos, readSize);
	m_cursorPos += readSize;

	return readSize;
}
