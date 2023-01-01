#pragma once

#include <set>
#include <algorithm>

#include "../Presenter/IMouseActionsHandler.h"

class MouseActionsDispatcher
{
public:
	void MouseDown(float x, float y);
	void MouseUp(float dx, float dy);
	void MouseDrag(float dx, float dy);

	void Subscribe(IMouseActionsHandler* handler);

private:
	void NotifyOnMouseDown(float x, float y);
	void NotifyOnMouseUp(float dx, float dy);
	void NotifyOnMouseDrag(float dx, float dy);

	std::set<IMouseActionsHandler*> m_handlers;
};
