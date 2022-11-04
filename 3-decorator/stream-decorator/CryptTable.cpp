#include "CryptTable.h"

CryptTable::CryptTable(Type type, size_t key)
{
	for (uint16_t i = 0; i < 256; ++i)
		m_data[i] = i;

	switch (type)
	{
	case CryptTable::Type::Encrypt:
		InitEncryptTable(key);
		break;
	case CryptTable::Type::Decrypt:
		InitDecryptTable(key);
		break;
	default:
		throw std::invalid_argument("Unknown crypt table type.");
	}
}

uint8_t CryptTable::operator[](uint8_t index) const
{
	return m_data[index];
}

void CryptTable::InitEncryptTable(size_t key)
{
	std::shuffle(m_data.begin(), m_data.end(), std::move(std::mt19937(key)));
}

void CryptTable::InitDecryptTable(size_t key)
{
	std::shuffle(m_data.begin(), m_data.end(), std::move(std::mt19937(key)));

	std::array<uint8_t, 256> inverted;
	for (uint16_t i = 0; i < 256; ++i)
		inverted[m_data[i]] = i;

	m_data = std::move(inverted);
}
