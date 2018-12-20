// Most of this file was created by Professor Dean Lawson.

#pragma once

#include <SDL.h>

#include <string>
#include <trackable.h>

using namespace std;

// the enums used to safely trasfer Allegro data
enum Key
{
	SPACE_KEY = SDLK_SPACE,
	UP_KEY = SDLK_UP,
	DOWN_KEY = SDLK_DOWN,
	LEFT_KEY = SDLK_LEFT,
	RIGHT_KEY = SDLK_RIGHT,

	ENTER_KEY = SDLK_RETURN,

	ESCAPE_KEY = SDLK_ESCAPE,

	W_KEY = SDLK_w,
	S_KEY = SDLK_s,
	A_KEY = SDLK_a,
	D_KEY = SDLK_d
};

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	KEY_PRESS_EVENT,
	UP_MOVE_EVENT,
	DOWN_MOVE_EVENT,
	LEFT_MOVE_EVENT,
	RIGHT_MOVE_EVENT,

	CREATE_UNIT_EVENT,
	DELETE_UNIT_EVENT,

	CHANGE_ANIMATION_EVENT,

	START_LEVEL_EVENT,
	SCORE_POINTS_EVENT,
	ADD_COINS_EVENT,
	GAME_OVER_EVENT,
	EXIT_GAME_EVENT,
	LOAD_GAME_EVENT,
	KEY_UP_EVENT,

	PLAY_SOUND_EFFECT_EVENT,
	PLAY_MUSIC_EVENT,

	TOGGLE_AUDIO_EVENT,
	SELECT_BUTTON_EVENT,
	CHANGE_DIFFICULTY_EVENT,
	START_LEVEL_GAMEPLAY_EVENT,

	ENVIRONMENT_MOVE_EVENT,

	KILL_PLAYER_CHARACTER_EVENT,
	GAMEOVER_EVENT,

	SET_POWER_UP_EVENT,
	WEAKEN_PLAYER_EVENT,

	END_OF_LEVEL_EVENT,
	WIN_GAME_EVENT,

	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = {	"Key Press Event",
												"Up Move Event",
												"Down Move Event",
												"Left Move Event",
												"Right Move Event",
												"Create Unit Event",
												"Delete Unit Event",
												"Change Animation Event",
												"Start Level Event",
												"Score Points Event",
												"Add Coins Event",
												"Game Over Event",
												"Exit Game Event",
												"Load Game Event",
												"Key Up Event",
												"Play Sound Effect Event",
												"Play Music Event",
												"Toggle Audio Event",
												"Select Button Event",
												"Start Level Gameplay Event",
												"Kill Player Character Event",
												"Gameover Event",
												"Change Difficulty Event",
												"Set Power Up Event",
												"Weaken Player Event",
												"End Of Level Event",
												"Win Game Event"
											};

class Event:public Trackable
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};