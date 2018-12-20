#include "MouseEvent.h"

// constructor for the MouseEvent class
MouseEvent::MouseEvent(int mouseValue, int x, int y)
	: Event(MOUSE_CLICK_EVENT)
{
	mClickedButton = mouseValue;
	mMousePos = Vector2D(x, y);
}

// destructor for the MouseEvent class
MouseEvent::~MouseEvent()
{

}

// gets the clicked mouse button
int MouseEvent::getClickedButton() const
{
	return mClickedButton;
}

// gets the current mouse position
Vector2D MouseEvent::getMousePos() const
{
	return mMousePos;
}