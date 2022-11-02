#ifndef I_INPUT_DATA_STREAM_H
#define I_INPUT_DATA_STREAM_H

#include <ios>
#include <memory>

class IInputDataStream
{
public:
	// ���������� ������� ���������� ����� ������ ������
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual bool IsEOF() const = 0;

	// ��������� ���� �� ������.
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual uint8_t ReadByte() = 0;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer
	// ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

	virtual ~IInputDataStream() = default;
};

typedef std::unique_ptr<IInputDataStream> InputDataStreamPtr;

#endif // !I_INPUT_DATA_STREAM_H
