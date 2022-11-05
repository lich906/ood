#ifndef ENCRYPT_OUTPUT_DATA_STREAM_DECORATOR_H
#define ENCRYPT_OUTPUT_DATA_STREAM_DECORATOR_H

#include "OutputDataStreamDecorator.h"
#include "CryptTable.h"

class EncryptOutputDataStreamDecorator : public OutputDataStreamDecorator
{
public:
	EncryptOutputDataStreamDecorator(OutputDataStreamPtr&& decoratedComponent, size_t key);

	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	const uint8_t* GetEncryptedBlock(const void* srcData, std::streamsize size) const;

	CryptTable m_encryptTable;
};

#endif // !ENCRYPT_OUTPUT_DATA_STREAM_DECORATOR_H
