#include "StateIntro.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateIntro::onCreate()
{
	this->timePassed = 0;

	sf::Vector2u windowSize = this->stateManager->getContext()->window->getRenderWindow()->getSize();

	this->spaceTexture.loadFromFile("Assets/space-logo.png");
	this->spaceSprite.setTexture(this->spaceTexture);
	this->spaceSprite.setOrigin({ static_cast<float>(this->spaceTexture.getSize().x) / 2, static_cast<float>(this->spaceTexture.getSize().y) / 2});
	this->spaceSprite.setPosition(windowSize.x / 2.0f - 260, 0);

	this->rocketTexture.loadFromFile("Assets/rocket-logo.png");
	this->rocketSprite.setTexture(this->rocketTexture);
	this->rocketSprite.setOrigin({ static_cast<float>(this->rocketTexture.getSize().x) / 2, static_cast<float>(this->rocketTexture.getSize().y) / 2 });
	this->rocketSprite.setPosition(windowSize.x / 2.0f, 0);

	this->craftTexture.loadFromFile("Assets/craft-logo.png");
	this->craftSprite.setTexture(this->craftTexture);
	this->craftSprite.setOrigin({ static_cast<float>(this->craftTexture.getSize().x) / 2, static_cast<float>(this->craftTexture.getSize().y) / 2 });
	this->craftSprite.setPosition(windowSize.x / 2.0f + 260, 0);

	this->font.loadFromFile("Michroma-Regular.ttf");

	this->madeByText.setString("Made by Kamil Luc");
	this->madeByText.setCharacterSize(30);
	this->madeByText.setFillColor(sf::Color::Black);
	this->madeByText.setOutlineColor(sf::Color::Black);
	this->madeByText.setFont(this->font);
	this->madeByText.setPosition({ 25.0f, static_cast<float>(windowSize.y - 25 - this->madeByText.getCharacterSize())});

	this->pressEnterText.setString("Press enter to continue");
	this->pressEnterText.setCharacterSize(30);
	this->pressEnterText.setFillColor(sf::Color::Black);
	this->pressEnterText.setOutlineColor(sf::Color::Black);
	this->pressEnterText.setFont(this->font);
	this->pressEnterText.setOrigin({ static_cast<float>(this->pressEnterText.getLocalBounds().width) / 2, static_cast<float>(this->pressEnterText.getLocalBounds().height) / 2 });
	this->pressEnterText.setPosition(windowSize.x / 2.0f, windowSize.y / 1.7f);
	this->pressEnterText.setScale(0.0f, 0.0f);

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
	float introMovementTime = 1.0f;

	if (this->timePassed < introMovementTime)
	{
		sf::Vector2u windowSize = this->stateManager->getContext()->window->getRenderWindow()->getSize();
		
		float yPos = (windowSize.y / 2.3f) * (this->timePassed / introMovementTime);

		this->spaceSprite.setPosition(this->spaceSprite.getPosition().x, yPos);
		this->craftSprite.setPosition(this->craftSprite.getPosition().x, yPos);

		float yPos2 = windowSize.y - windowSize.y * (this->timePassed / introMovementTime) + yPos;

		this->rocketSprite.setPosition(this->rocketSprite.getPosition().x, yPos2 - 10);
	}

	else if (this->timePassed > 2.0f)
	{
		float decimal = this->timePassed - static_cast<int>(this->timePassed);

		if (decimal < 0.5f)
		{
			this->pressEnterText.setScale(1.0f, 1.0f);
		}
		else
		{
			this->pressEnterText.setScale(0.0f, 0.0f);
		}
	}

	this->timePassed += time.asSeconds();
}

void StateIntro::draw()
{
	auto window = this->stateManager->getContext()->window->getRenderWindow();
	window->draw(this->spaceSprite);
	window->draw(this->rocketSprite);
	window->draw(this->craftSprite);
	window->draw(this->madeByText);
	window->draw(this->pressEnterText);
}

void StateIntro::skip(EventDetails* details)
{
	this->stateManager->switchTo(StateType::SpaceSimulation);
	this->stateManager->remove(StateType::Intro);
}
