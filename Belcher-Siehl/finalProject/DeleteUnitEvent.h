#pragma once
#include "Event.h"
#include "Vector2D.h"

// the DeleteUnitEvent class
class DeleteUnitEvent : public Event
{
public:
	// constructor and destructor
	DeleteUnitEvent(int x, int y);
	~DeleteUnitEvent();

	// accessors
	Vector2D getMouseLoc() const;

private:
	Vector2D mMouseLoc;
};