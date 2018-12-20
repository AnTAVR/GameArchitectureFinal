#pragma once

#include <Trackable.h>
#include "EventListener.h"

class EventSystem;

class ExampleListener : public EventListener
{
public:
	ExampleListener(EventSystem* pEventSystem);
	~ExampleListener();

	void handleEvent( const Event& theEvent );

private:
	static int msID;

	int mID;
};