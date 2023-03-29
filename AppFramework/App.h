#pragma once

#include "Window.h"

//test
#include "GUI/Textbox.h"
#include "StateManager/StateManager.h"

class App
{
public:
	App();
	~App();

	void handleInput();
	void update();
	void lateUpdate();
	void render();

	sf::Time getElapsedTime() const;
	void restartClock();

	Window* getWindow();

private:
	Window window;
	StateManager stateManager;

	SharedContext sharedContext;

	sf::Clock clock;
	sf::Time elapsedTime;

//test
	Textbox textbox;
};

