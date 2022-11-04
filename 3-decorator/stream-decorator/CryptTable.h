#ifndef CRYPT_TABLE_H
#define CRYPT_TABLE_H

#include <array>
#include <stdexcept>
#include <random>
#include <algorithm>

class CryptTable
{
public:
	enum class Type
	{
		Encrypt,
		Decrypt,
	};

	CryptTable(Type type, size_t key);

	uint8_t operator[](uint8_t index) const;

private:
	void InitEncryptTable(size_t key);
	void InitDecryptTable(size_t key);

	std::array<uint8_t, 256> m_data;
};

#endif // !CRYPT_TABLE_H
