#pragma once

#include <iostream>
#include <iomanip>

// ������������ ���� ����������� ���������� (���������� ��� ���������)
namespace graphics_lib
{
// ����� ��� ���������
class ICanvas
{
public:
	// ��������� ����� � ������� 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	// ������ "����" � ����� x, y
	virtual void MoveTo(int x, int y) = 0;
	// ������ ����� � ������� �������, ���������� ���� � ����� x,y
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// ���������� ������ ��� ���������
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		// TODO: ������� � output ���� � ���� ������ SetColor (#RRGGBB)
		std::cout << "SetColor (#" << std::setw(6) << std::setfill('0') << std::right << std::uppercase << std::hex << rgbColor << std::dec << std::nouppercase << ")" << std::endl;
	}
	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
} // namespace graphics_lib
