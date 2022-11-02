#ifndef INPUT_DATA_STREAM_DECORATOR_H
#define INPUT_DATA_STREAM_DECORATOR_H

#include "IInputDataStream.h"

class InputDataStreamDecorator : public IInputDataStream
{
public:
	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

protected:
	InputDataStreamDecorator(InputDataStreamPtr&& decoratedComponent);

private:
	InputDataStreamPtr m_wrappedComponent;
};

#endif // !INPUT_DATA_STREAM_DECORATOR_H
