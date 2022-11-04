#ifndef OUTPUT_DATA_STREAM_DECORATOR_H
#define OUTPUT_DATA_STREAM_DECORATOR_H

#include "IOutputDataStream.h"

class OutputDataStreamDecorator : public IOutputDataStream
{
protected:
	OutputDataStreamDecorator(OutputDataStreamPtr&& decoratedComponent);

	void WriteByte(uint8_t data);

	void WriteBlock(const void* srcData, std::streamsize size);

private:
	OutputDataStreamPtr m_wrappedComponent;
};

#endif // !OUTPUT_DATA_STREAM_DECORATOR_H
