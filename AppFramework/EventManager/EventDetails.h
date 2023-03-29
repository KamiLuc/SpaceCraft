#pragma once

#include <string>
#include <SFML/Window.hpp>

struct EventDetails
{
	EventDetails(const std::string& bindName)
		: name(bindName)
	{
		clear();
	}

	std::string name;
	sf::Vector2i size;
	sf::Uint32 textEntered;
	sf::Vector2i mouse;
	int mouseWheelDelta;
	int keyCode; // Single key code.

	void clear() {
		size = sf::Vector2i(0, 0);
		textEntered = 0;
		mouse = sf::Vector2i(0, 0);
		mouseWheelDelta = 0;
		keyCode = -1;
	}
};