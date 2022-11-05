#include "FileOutputDataStream.h"

FileOutputDataStream::FileOutputDataStream(const std::string& fileName)
	: m_stream(fileName, std::ios::binary)
{
	if (!m_stream.is_open())
	{
		throw std::runtime_error("Failed to open file '" + fileName + "'.");
	}
}

void FileOutputDataStream::WriteByte(uint8_t data)
{
	m_stream.put(data);
}

void FileOutputDataStream::WriteBlock(const void* srcData, std::streamsize size)
{
	if (srcData == nullptr)
	{
		throw std::invalid_argument("Source data buffer pointer is nullptr");
	}

	m_stream.write(reinterpret_cast<const char*>(srcData), size);
}
