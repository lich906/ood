#include "CompressOutputDataStreamDecorator.h"

CompressOutputDataStreamDecorator::CompressOutputDataStreamDecorator(OutputDataStreamPtr&& decoratedComponent)
	: OutputDataStreamDecorator(std::forward<OutputDataStreamPtr>(decoratedComponent))
{
}

void CompressOutputDataStreamDecorator::WriteByte(uint8_t data)
{
	if (!m_currSequenceData.lengthByte)
	{
		BeginNewSequence(data);
	}
	else if (m_currSequenceData.symbolCode != data || m_currSequenceData.lengthByte == 255)
	{
		WriteCurrentSequence();
		BeginNewSequence(data);
	}
	else
	{
		++m_currSequenceData.lengthByte;
	}
}

void CompressOutputDataStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	if (srcData == nullptr)
	{
		throw std::invalid_argument("Pointer to source data buffer is nullptr");
	}

	const uint8_t* data = reinterpret_cast<const uint8_t*>(srcData);

	for (std::streamsize i = 0; i < size; ++i)
	{
		WriteByte(data[i]);
	}

	WriteCurrentSequence();
}

CompressOutputDataStreamDecorator::~CompressOutputDataStreamDecorator()
{
	WriteCurrentSequence();
}

void CompressOutputDataStreamDecorator::WriteCurrentSequence()
{
	if (m_currSequenceData.lengthByte)
	{
		OutputDataStreamDecorator::WriteByte(m_currSequenceData.lengthByte);
		OutputDataStreamDecorator::WriteByte(m_currSequenceData.symbolCode);
	}

	m_currSequenceData.lengthByte = 0;
}

void CompressOutputDataStreamDecorator::BeginNewSequence(uint8_t symbolCode)
{
	m_currSequenceData.lengthByte = 1;
	m_currSequenceData.symbolCode = symbolCode;
}
