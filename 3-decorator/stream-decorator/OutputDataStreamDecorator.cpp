#include "OutputDataStreamDecorator.h"

OutputDataStreamDecorator::OutputDataStreamDecorator(OutputDataStreamPtr&& decoratedComponent)
	: m_wrappedComponent(std::move(decoratedComponent))
{
}

void OutputDataStreamDecorator::WriteByte(uint8_t data)
{
	m_wrappedComponent->WriteByte(data);
}

void OutputDataStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	m_wrappedComponent->WriteBlock(srcData, size);
}
