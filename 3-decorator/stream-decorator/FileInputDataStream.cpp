#include "FileInputDataStream.h"

FileInputDataStream::FileInputDataStream(const std::string& fileName)
	: m_stream(fileName, std::ios::binary)
{
	if (!m_stream.is_open())
	{
		throw std::runtime_error("Failed to open input stream.");
	}
}

bool FileInputDataStream::IsEOF() const
{
	if (m_stream.fail())
	{
		throw std::ios::failure("Unable to check end of file: Stream is in failure state");
	}

	return m_stream.eof();
}

uint8_t FileInputDataStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios::failure("Unable to read byte: Stream is empty");
	}

	return m_stream.get();
}

std::streamsize FileInputDataStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (dstBuffer == nullptr)
	{
		throw std::invalid_argument("Destionation buffer pointer is nullptr");
	}

	m_stream.read(reinterpret_cast<char*>(dstBuffer), size);
	return m_stream.gcount();
}
