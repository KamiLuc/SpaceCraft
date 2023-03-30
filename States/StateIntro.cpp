#include "StateIntro.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateIntro::onCreate()
{
	this->timePassed = 0;

	sf::Vector2u windowSize = this->stateManager->getContext()->window->getRenderWindow()->getSize();

	this->spaceTexture.loadFromFile("Assets/space-logo.png");
	this->spaceSprite.setTexture(this->spaceTexture);
	this->spaceSprite.setOrigin({ static_cast<float>(this->spaceTexture.getSize().x) / 2, static_cast<float>(this->spaceTexture.getSize().y) / 2});
	this->spaceSprite.setPosition(windowSize.x / 2 - 260, 0);

	this->rocketTexture.loadFromFile("Assets/rocket-logo.png");
	this->rocketSprite.setTexture(this->rocketTexture);
	this->rocketSprite.setOrigin({ static_cast<float>(this->rocketTexture.getSize().x) / 2, static_cast<float>(this->rocketTexture.getSize().y) / 2 });
	this->rocketSprite.setPosition(windowSize.x / 2, 0);

	this->craftTexture.loadFromFile("Assets/craft-logo.png");
	this->craftSprite.setTexture(this->craftTexture);
	this->craftSprite.setOrigin({ static_cast<float>(this->craftTexture.getSize().x) / 2, static_cast<float>(this->craftTexture.getSize().y) / 2 });
	this->craftSprite.setPosition(windowSize.x / 2 + 260, 0);

	this->madeByTexture.loadFromFile("Assets/made-by.png");
	this->madeBySprite.setTexture(this->madeByTexture);

	this->pressEnterTexture.loadFromFile("Assets/press-enter.png");
	this->pressEnterSprite.setTexture(this->pressEnterTexture);

	this->madeBySprite.setPosition({25.0f, static_cast<float>(windowSize.y - 25 - this->madeByTexture.getSize().y)});

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
	if (this->timePassed < 5.0f)
	{
		this->timePassed += time.asSeconds();

		this->spaceSprite.setPosition(this->spaceSprite.getPosition().x, this->spaceSprite.getPosition().y + (48 * time.asSeconds()));
	}
	else {
		int x = 0;
	}
}

void StateIntro::draw()
{
	auto window = this->stateManager->getContext()->window->getRenderWindow();
	window->draw(this->spaceSprite);
	window->draw(this->rocketSprite);
	window->draw(this->craftSprite);
	window->draw(this->madeBySprite);
}

void StateIntro::skip(EventDetails* details)
{
}
