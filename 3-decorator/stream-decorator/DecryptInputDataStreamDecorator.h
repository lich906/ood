#ifndef DECRYPT_INPUT_DATA_STREAM_DECORATOR_H
#define DECRYPT_INPUT_DATA_STREAM_DECORATOR_H

#include "InputDataStreamDecorator.h"
#include "CryptTable.h"

class DecryptInputDataStreamDecorator : public InputDataStreamDecorator
{
public:
	DecryptInputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent, size_t key);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	void DecryptBlock(void* dstBuffer, std::streamsize size) const;

	CryptTable m_decryptTable;
};

#endif // !DECRYPT_INPUT_DATA_STREAM_DECORATOR_H
