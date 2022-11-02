#ifndef DECOMPRESS_INPUT_DATA_STREAM_DECORATOR_H
#define DECOMPRESS_INPUT_DATA_STREAM_DECORATOR_H

#include "InputDataStreamDecorator.h"

class DecompressInputDataStreamDecorator : public InputDataStreamDecorator
{
public:
	DecompressInputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	struct SequenceData
	{
		uint8_t lengthByte = 0;
		uint8_t symbolCode = 0;
	} m_currSequenceData;
};

#endif // !DECOMPRESS_INPUT_DATA_STREAM_DECORATOR_H
