#ifndef COMPRESS_OUTPUT_DATA_STREAM_DECORATOR_H
#define COMPRESS_OUTPUT_DATA_STREAM_DECORATOR_H

#include "OutputDataStreamDecorator.h"

class CompressOutputDataStreamDecorator : public OutputDataStreamDecorator
{
public:
	CompressOutputDataStreamDecorator(OutputDataStreamPtr&& decoratedComponent);

	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

	~CompressOutputDataStreamDecorator();

private:
	void WriteCurrentSequence();

	void BeginNewSequence(uint8_t symbolCode);

	struct SequenceData
	{
		uint8_t lengthByte = 0;
		uint8_t symbolCode = 0;
	} m_currSequenceData;
};

#endif // !COMPRESS_OUTPUT_DATA_STREAM_DECORATOR_H
