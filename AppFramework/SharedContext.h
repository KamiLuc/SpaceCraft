#pragma once

#include "Window.h"

struct SharedContext
{
	SharedContext() : window(nullptr), eventManager(nullptr) {}

	Window* window;
	EventManager* eventManager;
};