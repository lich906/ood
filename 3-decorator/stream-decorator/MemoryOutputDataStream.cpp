#include "MemoryOutputDataStream.h"

void MemoryOutputDataStream::WriteByte(uint8_t data)
{
	m_data.emplace_back(data);
}

void MemoryOutputDataStream::WriteBlock(const void* srcData, std::streamsize size)
{
	if (srcData == nullptr)
	{
		throw std::invalid_argument("Source data buffer pointer is nullptr");
	}

	size_t i = 0;
	for (const char* srcPtr = reinterpret_cast<const char*>(srcData); i < size && srcPtr != nullptr; ++srcPtr, ++i)
	{
		m_data.push_back(*srcPtr);
	}
}
