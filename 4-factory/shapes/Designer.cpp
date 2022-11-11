#include "Designer.h"

Designer::Designer(ShapeFactoryPtr&& shapeFactoryPtr)
	: m_shapeFactory(std::forward<ShapeFactoryPtr>(shapeFactoryPtr))
{
}

PictureDraft Designer::CreateDraft(std::istream& stream) const
{
	PictureDraft draft;

	std::string shapeDescription;
	for (size_t lineNumber = 1; std::getline(stream, shapeDescription); ++lineNumber)
	{
		try
		{
			draft.AddShape(m_shapeFactory->CreateShape(shapeDescription));
		}
		catch (const std::exception& e)
		{
			std::cout << "Warning: " << e.what() << " at line: " << lineNumber << " Skipping this line..." << std::endl;
		}
	}

	return draft;
}
