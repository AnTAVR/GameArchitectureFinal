#include "StringEvent.h"

StringEvent::StringEvent(const string& theString)
	:Event( STRING_EVENT )
,mString(theString)
{
}

StringEvent::~StringEvent()
{
}
