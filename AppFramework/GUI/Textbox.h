#pragma once

#include <SFML/Graphics.hpp>

class Textbox
{
public:
	Textbox();
	Textbox(unsigned int linesVisible, unsigned int characterSize, unsigned int widht, const sf::Vector2f& screenPosition);
	~Textbox();

	void setup(int linesVisible, int characterSize, int width, const sf::Vector2f& screenPosition);
	void addMessage(std::string message);
	void clear();
	void render(sf::RenderWindow& window);

private:
	std::vector<std::string> messages;
	int linesVisible;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text content;
};

