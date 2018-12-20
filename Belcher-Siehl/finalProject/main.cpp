/*
Author: Cameron Belcher & Joseph Siehl
Class: EGP-310-02
Assignment: Final Project
Certification of Authenticity: 
I certify that this assignment is entirely my own work.
*/

#include "Game.h"
#include "EventSystem.h"

#include "SDL_main.h"

#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
	// initializes the static EventSystem object
	EventSystem::initInstance();

	// initializes the static Game object
	Game::initInstance();
	Game::getInstance()->init();

	// performs the Gameplay loop
	Game::getInstance()->doLoop();

	// cleans up the display
	Game::cleanupInstance();
	EventSystem::cleanupInstance();

	// reports any memory leaks and closes the program
	gMemoryTracker.reportAllocations(cout);
	system("pause");

	return 0;
}