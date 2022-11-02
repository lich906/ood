#ifndef I_OUTPUT_DATA_STREAM_H
#define I_OUTPUT_DATA_STREAM_H

#include "common.h"

class IOutputDataStream
{
public:
	// Записывает в поток данных байт
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	virtual void WriteByte(uint8_t data) = 0;

	// Записывает в поток блок данных размером size байт,
	// располагающийся по адресу srcData,
	// В случае ошибки выбрасывает исключение std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() = default;
};


#endif // !I_OUTPUT_DATA_STREAM_H
