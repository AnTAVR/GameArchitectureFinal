#include "DeleteUnitEvent.h"

// constructor for the DeleteUnitEvent class
DeleteUnitEvent::DeleteUnitEvent(int x, int y)
	: Event(DELETE_UNIT_EVENT)
{
	mMouseLoc = Vector2D(x, y);
}

// destructor for the DeleteUnitEvent class
DeleteUnitEvent::~DeleteUnitEvent()
{

}

// returns the current mouse position
Vector2D DeleteUnitEvent::getMouseLoc() const
{
	return mMouseLoc;
}