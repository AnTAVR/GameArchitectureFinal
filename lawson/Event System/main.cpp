
#include <iostream>
#include <string>

#include <Trackable.h>
#include <MemoryTracker.h>

#include <Timer.h>
#include <PerformanceTracker.h>
#include <Vector2D.h>

#include "EventSystem.h"
#include "ExampleListener.h"
#include "MoveEvent.h"
#include "StringEvent.h"

int main()
{
	EventSystem* pEventSystem = new EventSystem();
	EventSystem* pEventSystem2 = new EventSystem();

	ExampleListener* pListener = new ExampleListener(pEventSystem);
	ExampleListener* pListener2 = new ExampleListener(pEventSystem2);
	ExampleListener* pListener3 = new ExampleListener(pEventSystem);

	//fire some events
	pEventSystem->fireEvent( MoveEvent( Vector2D( 1.0f, 2.0f ) ) );

	pEventSystem->fireEvent( StringEvent( "Initialization complete" ) );

	pEventSystem->fireEvent( StringEvent( "Text1" ) );

	//wait a bit
	/*Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(1000);*/

	//fire some more events
	pEventSystem->fireEvent( StringEvent( "Text2" ) );

	pEventSystem2->fireEvent( StringEvent( "Text3" ) );

	pEventSystem->fireEvent( StringEvent( "Text4" ) );

	delete pListener;//make sure you delete listeners before the event system they use
	delete pListener2;//make sure you delete listeners before the event system they use
	delete pListener3;//make sure you delete listeners before the event system they use
	delete pEventSystem;
	delete pEventSystem2;
	//delete pTimer;

	gMemoryTracker.reportAllocations(std::cout);

	system("pause");

	return 0;
}