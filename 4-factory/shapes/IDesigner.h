#ifndef I_DESIGNER_H
#define I_DESIGNER_H

#include <iostream>

#include "PictureDraft.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;

	virtual PictureDraft CreateDraft(std::istream& stream) const = 0;
};

#endif // !I_DESIGNER_H
