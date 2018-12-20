#include "ExampleListener.h"
#include "EventSystem.h"
#include "Event.h"
#include "MoveEvent.h"
#include "StringEvent.h"

int ExampleListener::msID = 0;

ExampleListener::ExampleListener(EventSystem* pEventSystem)
:EventListener(pEventSystem)
,mID(msID)
{
	msID++;
	pEventSystem->addListener( MOVE_EVENT, this );
	pEventSystem->addListener( STRING_EVENT, this );
}

ExampleListener::~ExampleListener()
{}

void ExampleListener::handleEvent(const Event &theEvent)
{
	cout << endl << "ExampleListener#" << mID << endl;
	cout << "\t" << theEvent.getEventName() << " Received";
	
	if( theEvent.getType() == MOVE_EVENT )
	{
		const MoveEvent& moveEvent = static_cast<const MoveEvent&>(theEvent);
		cout	<< endl << "\tMove to: " << moveEvent.getLocation().getX()
				<< "," << moveEvent.getLocation().getY();
	}
	else if( theEvent.getType() == STRING_EVENT )
	{
		const StringEvent& stringEvent = static_cast<const StringEvent&>(theEvent);
		cout	<< endl << "\tMessage: " << stringEvent.getString();
	}
}