#include "StateIntro.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateIntro::onCreate()
{
	this->timePassed = 0;

	sf::Vector2u windowSize = this->stateManager->getContext()->window->getRenderWindow()->getSize();
}

void StateIntro::onDestroy()
{
}

void StateIntro::activate()
{
}

void StateIntro::deactivate()
{
}

void StateIntro::update(const sf::Time& time)
{
}

void StateIntro::draw()
{
}
