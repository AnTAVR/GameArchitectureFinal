// Most of this file was created by Professor Dean Lawson.

#pragma once

#include <map>
#include <Trackable.h>

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem:public Trackable
{
public:
	EventSystem();
	~EventSystem();

	void fireEvent( const Event& theEvent );
	void addListener( EventType type, EventListener* pListener );
	void removeListener( EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

	// functions for the static class
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanupInstance();

private:
	static EventSystem* mpsInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents( const Event& theEvent );

};

