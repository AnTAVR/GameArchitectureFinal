#pragma once

#include "Event.h"
#include "Vector2D.h"

// the MouseEvent class
class MouseEvent : public Event
{
public:
	// constructor and destructor
	MouseEvent(int mouseValue, int x, int y);
	~MouseEvent();

	// accessors
	int getClickedButton() const;
	Vector2D getMousePos() const;

private:
	int mClickedButton;
	Vector2D mMousePos;
};