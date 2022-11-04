#include "DecryptInputDataStreamDecorator.h"

DecryptInputDataStreamDecorator::DecryptInputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent, size_t key)
	: InputDataStreamDecorator(std::forward<InputDataStreamPtr>(decoratedComponent))
	, m_decryptTable(CryptTable::Type::Decrypt, key)
{
}

bool DecryptInputDataStreamDecorator::IsEOF() const
{
	return InputDataStreamDecorator::IsEOF();
}

uint8_t DecryptInputDataStreamDecorator::ReadByte()
{
	return m_decryptTable[InputDataStreamDecorator::ReadByte()];
}

std::streamsize DecryptInputDataStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto readSize = InputDataStreamDecorator::ReadBlock(dstBuffer, size);
	DecryptBlock(dstBuffer, size);

	return readSize;
}

void DecryptInputDataStreamDecorator::DecryptBlock(void* dstBuffer, std::streamsize size) const
{
	uint8_t* byteBuffer = reinterpret_cast<uint8_t*>(dstBuffer);

	for (std::streamsize i = 0; i < size; ++i)
	{
		byteBuffer[i] = m_decryptTable[byteBuffer[i]];
	}
}
