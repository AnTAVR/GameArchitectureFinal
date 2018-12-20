#include "CreateUnitEvent.h"

// constructor for the CreateUnitEvent class
CreateUnitEvent::CreateUnitEvent(int x, int y)
	: Event(CREATE_UNIT_EVENT)
{
	mMouseLoc = Vector2D(x, y);
}

// destructor for the CreateUnitEvent class
CreateUnitEvent::~CreateUnitEvent()
{

}

// returns the current mouse position
Vector2D CreateUnitEvent::getMouseLoc() const
{
	return mMouseLoc;
}