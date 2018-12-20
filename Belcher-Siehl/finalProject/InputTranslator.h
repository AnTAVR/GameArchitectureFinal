#pragma once

#include "EventListener.h"
#include "EventSystem.h"

#include <MemoryTracker.h>
#include <PerformanceTracker.h>

// the InputTranslator class
class InputTranslator : public EventListener
{
public:
	// constructors and destructor
	InputTranslator(EventSystem* pEventSystem);
	~InputTranslator();

	// initializes the class object
	int init();

	// cleans up any remaining memory
	void cleanup();

	// handles the event
	void handleEvent(const Event& theEvent);

private:
	bool mIsInit;
	bool mIsCleanup;
};