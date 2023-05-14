#pragma once

#include "Window.h"
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
	ShaderManager shaderManager;
	TextureManager texturesManager;

	SharedContext sharedContext;

	sf::Clock clock;
	sf::Time elapsedTime;
};

