#include "FileInputDataStream.h"

FileInputDataStream::FileInputDataStream(const std::string& fileName)
	: m_stream(fileName, std::ios::binary)
{
	if (!m_stream.is_open())
	{
		throw std::runtime_error("Failed to open file '" + fileName + "'.");
	}

	DetermineFileSize();
}

bool FileInputDataStream::IsEOF() const
{
	if (m_stream.bad())
	{
		throw std::ios::failure("Unable to check end of file: Stream is in unrecoverable bad state");
	}

	return m_stream.tellg() == m_fileSize;
}

uint8_t FileInputDataStream::ReadByte()
{
	if (!m_stream)
	{
		throw std::ios::failure("Unable to read byte: Stream is in failure state");
	}

	return static_cast<uint8_t>(m_stream.get());
}

std::streamsize FileInputDataStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (dstBuffer == nullptr)
	{
		throw std::invalid_argument("Destionation buffer pointer is nullptr");
	}

	return m_stream.read(reinterpret_cast<char*>(dstBuffer), size).gcount();
}

void FileInputDataStream::DetermineFileSize()
{
	m_stream.seekg(0, std::ios::end);
	m_fileSize = m_stream.tellg();
	m_stream.seekg(0, std::ios::beg);
}
