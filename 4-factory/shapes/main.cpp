#include <iostream>

#include "ShapeFactory.h"
#include "Designer.h"
#include "Painter.h"
#include "SFMLCanvas.h"

std::string GetImageFileName(int argc, char** argv);

int main(int argc, char** argv)
try
{
	std::string imageFileName = GetImageFileName(argc, argv);

	Designer designer(std::make_unique<ShapeFactory>());
	Painter painter;
	auto canvas = std::make_unique<SFMLCanvas>(800, 600);

	painter.DrawPicture(designer.CreateDraft(std::cin), canvas.get());

	canvas->SaveImageToFile(imageFileName);

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
	return 1;
}

std::string GetImageFileName(int argc, char** argv)
{
	if (argc != 2)
	{
		throw std::invalid_argument("Please, specify only output image file.\n"
									"Usage: shapes.exe FILE_NAME\n"
									"\tSupported image formats bmp, png, tga, jpg");
	}

	return argv[1];
}
