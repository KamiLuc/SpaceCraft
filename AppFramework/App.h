#pragma once

#include "Window.h"
#include "StateManager/StateManager.h"
#include "Settings/Settings.h"

class App
{
public:
	App();
	~App();

	void handleInput();
	void update();
	void lateUpdate();
	void render();
	void restartClock();
	sf::Time getElapsedTime() const;
	Window* getWindow();

private:
	Window window;
	StateManager stateManager;
	std::shared_ptr<ShaderManager>shaderManager;
	std::shared_ptr<TextureManager>textureManager;
	SharedContext sharedContext;
	sf::Clock clock;
	sf::Time elapsedTime;
};

