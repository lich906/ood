#ifndef I_OUTPUT_DATA_STREAM_H
#define I_OUTPUT_DATA_STREAM_H

#include <ios>
#include <memory>

class IOutputDataStream
{
public:
	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual void WriteByte(uint8_t data) = 0;

	// ���������� � ����� ���� ������ �������� size ����,
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() = default;
};

typedef std::unique_ptr<IOutputDataStream> OutputDataStreamPtr;

#endif // !I_OUTPUT_DATA_STREAM_H
