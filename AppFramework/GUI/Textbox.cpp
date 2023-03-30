#include "Textbox.h"

Textbox::Textbox()
{
	this->setup(5, 9, 200, { 0,0 });
}

Textbox::Textbox(unsigned int visible, unsigned int charSize, unsigned int width, const sf::Vector2f& screenPosition)
{
	this->setup(visible, charSize, width, screenPosition);
}

Textbox::~Textbox()
{
	this->clear();
}

void Textbox::setup(int linesVisible, int characterSize, int width, const sf::Vector2f& screenPosition)
{
	this->linesVisible = linesVisible;
	sf::Vector2f offset{ 2.0f, 2.0f };

	this->font.loadFromFile("arial.ttf");
	this->content.setFont(this->font);
	this->content.setString("");
	this->content.setCharacterSize(characterSize);
	this->content.setFillColor(sf::Color::White);
	this->content.setOutlineColor(sf::Color::White);
	this->content.setPosition(screenPosition + offset);

	this->background.setSize({static_cast<float>(width), linesVisible * (characterSize * 1.2f)});
	this->background.setFillColor(sf::Color(90, 90, 90, 90));
	this->background.setPosition(screenPosition);
}

void Textbox::addMessage(std::string message)
{
	this->messages.push_back(message);
	if (messages.size() > this->linesVisible)
	{
		this->messages.erase(this->messages.begin());
	}
}

void Textbox::clear()
{
	this->messages.clear();
}

void Textbox::render(sf::RenderWindow& window)
{
	std::string content;

	for (auto& message : this->messages)
	{
		content.append(message + "\n");
	}

	if (content.size() > 0)
	{
		this->content.setString(content);
		window.draw(this->content);
		window.draw(this->background);
	}
}

