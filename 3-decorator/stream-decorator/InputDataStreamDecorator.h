#ifndef INPUT_DATA_STREAM_DECORATOR_H
#define INPUT_DATA_STREAM_DECORATOR_H

#include "IInputDataStream.h"

class InputDataStreamDecorator : public IInputDataStream
{
public:
	InputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	InputDataStreamPtr m_wrappedComponent;
};

#endif // !INPUT_DATA_STREAM_DECORATOR_H
