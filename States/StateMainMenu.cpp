#include "StateMainMenu.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateMainMenu::onCreate()
{
	auto window = this->stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::White);

	unsigned int characterSize = windowSize.y / 20;

	this->font.loadFromFile("Michroma-Regular.ttf");
	this->text.setFont(this->font);

	std::vector<std::string> menuStrings = { "New simulation", "Load simulation", "Options", "Source code", "Exit" };

	for (size_t i = 0; i < menuStrings.size(); i++)
	{
		sf::Text label(menuStrings[i], this->font, characterSize);
		label.setFillColor(sf::Color::Black);
		label.setOrigin(label.getLocalBounds().width / 2, label.getLocalBounds().height);
		label.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y / 10 * (i + 1)));

		this->menuLabels.push_back(label);
	}
}

void StateMainMenu::onDestroy()
{
}

void StateMainMenu::activate()
{
}

void StateMainMenu::deactivate()
{
}

void StateMainMenu::update(const sf::Time& time)
{
}

void StateMainMenu::draw()
{
	sf::RenderWindow* window = this->stateManager->getContext()->window->getRenderWindow();

	for (size_t i = 0; i < this->menuLabels.size(); i++)
	{
		window->draw(this->menuLabels.at(i));
	}
}
