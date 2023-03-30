#include "StateMainMenu.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateMainMenu::onCreate()
{
	this->stateManager->getContext()->window->setClearColor(sf::Color::Green);
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
	int x = 0;
}

void StateMainMenu::draw()
{
}
