#pragma once
#include "Event.h"

class ChangeDifficultyEvent : public Event
{
public:
	ChangeDifficultyEvent();
	~ChangeDifficultyEvent();
};