#pragma once

struct IMouseActionsHandler
{
	virtual ~IMouseActionsHandler() = default;

	virtual void OnMouseDown(float x, float y) = 0;
	virtual void OnMouseUp(float dx, float dy) = 0;
	virtual void OnMouseDrag(float dx, float dy) = 0;
};
