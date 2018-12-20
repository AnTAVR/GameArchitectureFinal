#pragma once
#include "Event.h"
#include "Vector2D.h"

// the CreateUnitEvent class
class CreateUnitEvent : public Event
{
public:
	// constructor and destructor
	CreateUnitEvent(int x, int y);
	~CreateUnitEvent();

	// accessors
	Vector2D getMouseLoc() const;

private:
	Vector2D mMouseLoc;
};