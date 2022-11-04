#include "DecompressInputDataStreamDecorator.h"

DecompressInputDataStreamDecorator::DecompressInputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent)
	: InputDataStreamDecorator(std::forward<InputDataStreamPtr>(decoratedComponent))
{
}

bool DecompressInputDataStreamDecorator::IsEOF() const
{
	return InputDataStreamDecorator::IsEOF() && !m_currSequenceData.lengthByte;
}

uint8_t DecompressInputDataStreamDecorator::ReadByte()
{
	if (!m_currSequenceData.lengthByte)
	{
		m_currSequenceData.lengthByte = InputDataStreamDecorator::ReadByte();

		if (!m_currSequenceData.lengthByte)
		{
			throw std::ios::failure("Error was occured during decompression: Length byte cannot be zero");
		}

		m_currSequenceData.symbolCode = InputDataStreamDecorator::ReadByte();
	}

	--m_currSequenceData.lengthByte;

	return m_currSequenceData.symbolCode;
}

std::streamsize DecompressInputDataStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (dstBuffer == nullptr)
	{
		throw std::invalid_argument("Destionation buffer pointer is nullptr");
	}

	uint8_t* dst = reinterpret_cast<uint8_t*>(dstBuffer);

	std::streamsize count = 0;
	for (; count < size; ++count)
		*dst++ = ReadByte();

	return count;
}
