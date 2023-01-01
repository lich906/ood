#include "..\..\include\View\MouseActionsDispatcher.h"

void MouseActionsDispatcher::MouseDown(float x, float y)
{
	NotifyOnMouseDown(x, y);
}

void MouseActionsDispatcher::MouseUp(float dx, float dy)
{
	NotifyOnMouseUp(dx, dy);
}

void MouseActionsDispatcher::MouseDrag(float dx, float dy)
{
	NotifyOnMouseDrag(dx, dy);
}

void MouseActionsDispatcher::Subscribe(IMouseActionsHandler* handler)
{
	m_handlers.insert(handler);
}

void MouseActionsDispatcher::NotifyOnMouseDown(float x, float y)
{
	std::for_each(m_handlers.begin(), m_handlers.end(), [=](IMouseActionsHandler* handler) {
		handler->OnMouseDown(x, y);
	});
}

void MouseActionsDispatcher::NotifyOnMouseUp(float dx, float dy)
{
	std::for_each(m_handlers.begin(), m_handlers.end(), [=](IMouseActionsHandler* handler) {
		handler->OnMouseUp(dx, dy);
	});
}

void MouseActionsDispatcher::NotifyOnMouseDrag(float dx, float dy)
{
	std::for_each(m_handlers.begin(), m_handlers.end(), [=](IMouseActionsHandler* handler) {
		handler->OnMouseDrag(dx, dy);
	});
}
