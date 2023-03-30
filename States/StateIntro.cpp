#include "StateIntro.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateIntro::onCreate()
{
	this->timePassed = 0;

	sf::Vector2u windowSize = this->stateManager->getContext()->window->getRenderWindow()->getSize();

	this->craftTexture.loadFromFile("Assets/craft-logo.png");
	this->craftSprite.setTexture(this->craftTexture);

	this->madeByTexture.loadFromFile("Assets/made-by.png");
	this->madeBySprite.setTexture(this->madeByTexture);

	this->madeBySprite.setPosition({25.0f, static_cast<float>(windowSize.y - 25 - this->madeByTexture.getSize().y)});

	this->craftSprite.setPosition({ 50,50 });
	
	this->stateManager->getContext()->eventManager->addCallback(StateType::Intro, "Skip_Intro", &StateIntro::skip, this);
}

void StateIntro::onDestroy()
{
	this->stateManager->getContext()->eventManager->removeCallback(StateType::Intro, "Skip_Intro");
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
	auto window = this->stateManager->getContext()->window->getRenderWindow();
	//window->draw(this->spaceSprite);
	window->draw(this->craftSprite);
	window->draw(this->madeBySprite);
	//window->draw(this->rocketSprite);
	//window->draw(this->madeBySprite);
	/*
	if (this->timePassed >= 4.0f)
	{
		window->draw(this->craftSprite);
	}
	*/
}

void StateIntro::skip(EventDetails* details)
{
}
