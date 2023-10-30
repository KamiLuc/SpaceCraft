#pragma once

#include "EventManager/EventManager.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <GL\glew.h>

enum class Render
{
	twoDimensional = 0,
	threeDimensional = 1
};

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size, const sf::Color& clearColor);
	~Window();

	void beginDraw();
	void endDraw();
	void update();
	void setWindowSize(const sf::Vector2u& size);
	void setClearColor(const sf::Color& color);
	void close(EventDetails* details = nullptr);
	void draw(const sf::Drawable& drawable);
	void renderImGui();
	void start2D();
	void start3D();
	void startWindow();
	bool isDone() const;
	bool isFocused() const;
	bool isFullscreen() const;
	sf::Vector2u getWindowSize() const;
	sf::Vector2i getMousePosition() const;
	sf::RenderWindow* getRenderWindow();
	EventManager* getEventManager();
	sf::Color getClearColor() const;

private:
	Render currentRender;
	sf::RenderWindow window;
	EventManager eventManager;
	sf::Vector2u windowSize;
	std::string windowTitle;
	sf::Color clearColor;
	sf::Clock imGuiUpdateClock;
	bool done;
	bool fullscreen;
	bool focused;

	void destroy();
	void create();
	void initGLEW();
};

