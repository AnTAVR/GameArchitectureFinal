#pragma once

#include <allegro5/allegro.h>

#include "EventListener.h"

// the InputListener class
class InputEventListener : public EventListener
{
public:
	// constructor and destructor
	InputEventListener();
	~InputEventListener();

	// handle the Event
	void handleEvent(const Event& theEvent);
};