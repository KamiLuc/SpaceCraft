#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <GL\glew.h>

#include "EventManager/EventManager.h"

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size, const sf::Color& clearColor);
	~Window();

	void beginDraw();
	void endDraw();
	void update();
	void close(EventDetails* details = nullptr);
	void toggleFullscreen(EventDetails* details);
	void draw(const sf::Drawable& drawable);

	void start2D();
	void stop2D();
	void start3D();
	void stop3D();

	bool isDone() const;
	bool isFocused() const;
	bool isFullscreen() const;
	sf::Vector2u getWindowSize() const;
	sf::RenderWindow* getRenderWindow();
	EventManager* getEventManager();

	void setClearColor(const sf::Color& color);

private:
	void destroy();
	void create();
	void initGLEW();

	sf::RenderWindow window;
	EventManager eventManager;
	sf::Vector2u windowSize;
	std::string windowTitle;
	sf::Color clearColor;
	bool done;
	bool fullscreen;
	bool focused;
};

