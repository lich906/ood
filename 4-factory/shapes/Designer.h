#ifndef DESIGNER_H
#define DESIGNER_H

#include "IDesigner.h"
#include "IShapeFactory.h"

class Designer : public IDesigner
{
public:
	Designer(ShapeFactoryPtr&& shapeFactoryPtr);

	PictureDraft CreateDraft(std::istream& stream) const override;

private:
	ShapeFactoryPtr m_shapeFactory;
};

#endif // !DESIGNER_H
