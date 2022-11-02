#include "InputDataStreamDecorator.h"

InputDataStreamDecorator::InputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent)
	: m_wrappedComponent(std::move(decoratedComponent))
{
}

bool InputDataStreamDecorator::IsEOF() const
{
	return m_wrappedComponent->IsEOF();
}

uint8_t InputDataStreamDecorator::ReadByte()
{
	return m_wrappedComponent->ReadByte();
}

std::streamsize InputDataStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	return m_wrappedComponent->ReadBlock(dstBuffer, size);
}
