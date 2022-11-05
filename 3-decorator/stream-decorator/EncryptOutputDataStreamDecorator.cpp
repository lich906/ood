#include "EncryptOutputDataStreamDecorator.h"

EncryptOutputDataStreamDecorator::EncryptOutputDataStreamDecorator(OutputDataStreamPtr&& decoratedComponent, size_t key)
	: OutputDataStreamDecorator(std::forward<OutputDataStreamPtr>(decoratedComponent))
	, m_encryptTable(CryptTable::Type::Encrypt, key)
{
}

void EncryptOutputDataStreamDecorator::WriteByte(uint8_t data)
{
	OutputDataStreamDecorator::WriteByte(m_encryptTable[data]);
}

void EncryptOutputDataStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	if (srcData == nullptr)
	{
		throw std::invalid_argument("Pointer to source data buffer is nullptr");
	}

	auto encryptedBlock = GetEncryptedBlock(srcData, size);
	OutputDataStreamDecorator::WriteBlock(encryptedBlock, size);
	delete[] encryptedBlock;
}

const uint8_t* EncryptOutputDataStreamDecorator::GetEncryptedBlock(const void* srcData, std::streamsize size) const
{
	auto encrypted = new uint8_t[size]();
	const uint8_t* srcByteData = reinterpret_cast<const uint8_t*>(srcData);

	for (std::streamsize i = 0; i < size; ++i)
	{
		encrypted[i] = m_encryptTable[srcByteData[i]];
	}

	return encrypted;
}
