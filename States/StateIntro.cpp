#include "StateIntro.h"

StateIntro::StateIntro(StateManager* stateManager, Render render)
	: BaseState(stateManager, render)
	, introMovementTimInSec(1.0f)
	, timePassedInSec(0.0f)
{
}

void StateIntro::onCreate()
{
	sf::Vector2u windowSize = stateManager->getContext()->window->getRenderWindow()->getSize();

	spaceTexture.loadFromFile("Assets/space-logo.png");
	spaceSprite.setTexture(spaceTexture);
	spaceSprite.setOrigin({ static_cast<float>(spaceTexture.getSize().x) / 2, static_cast<float>(spaceTexture.getSize().y) / 2 });
	spaceSprite.setPosition(windowSize.x / 2.0f - 260, 0);

	rocketTexture.loadFromFile("Assets/rocket-logo.png");
	rocketSprite.setTexture(rocketTexture);
	rocketSprite.setOrigin({ static_cast<float>(rocketTexture.getSize().x) / 2, static_cast<float>(rocketTexture.getSize().y) / 2 });
	rocketSprite.setPosition(windowSize.x / 2.0f, 0);

	craftTexture.loadFromFile("Assets/craft-logo.png");
	craftSprite.setTexture(craftTexture);
	craftSprite.setOrigin({ static_cast<float>(craftTexture.getSize().x) / 2, static_cast<float>(craftTexture.getSize().y) / 2 });
	craftSprite.setPosition(windowSize.x / 2.0f + 260, 0);

	font.loadFromFile("Michroma-Regular.ttf");

	madeByText.setString("Made by Kamil Luc");
	madeByText.setCharacterSize(30);
	madeByText.setFillColor(sf::Color::Black);
	madeByText.setOutlineColor(sf::Color::Black);
	madeByText.setFont(font);
	madeByText.setPosition({ 25.0f, static_cast<float>(windowSize.y - 25 - madeByText.getCharacterSize()) });

	pressEnterText.setString("Press enter to continue");
	pressEnterText.setCharacterSize(30);
	pressEnterText.setFillColor(sf::Color::Black);
	pressEnterText.setOutlineColor(sf::Color::Black);
	pressEnterText.setFont(font);
	pressEnterText.setOrigin({ static_cast<float>(pressEnterText.getLocalBounds().width) / 2, static_cast<float>(pressEnterText.getLocalBounds().height) / 2 });
	pressEnterText.setPosition(windowSize.x / 2.0f, windowSize.y / 1.7f);
	pressEnterText.setScale(0.0f, 0.0f);

	stateManager->getContext()->eventManager->addCallback(StateType::Intro, "Skip_Intro", &StateIntro::skip, this);
}

void StateIntro::onDestroy()
{
	stateManager->getContext()->eventManager->removeCallback(StateType::Intro, "Skip_Intro");
}

void StateIntro::activate()
{
}

void StateIntro::deactivate()
{
}

void StateIntro::update(const sf::Time& time)
{
	sf::Vector2u windowSize = stateManager->getContext()->window->getRenderWindow()->getSize();
	float yPos = (windowSize.y / 2.3f);

	if (timePassedInSec < introMovementTimInSec)
	{
		spaceSprite.setPosition(spaceSprite.getPosition().x, yPos * (timePassedInSec / introMovementTimInSec));
		craftSprite.setPosition(craftSprite.getPosition().x, yPos * (timePassedInSec / introMovementTimInSec));
		rocketSprite.setPosition(rocketSprite.getPosition().x, windowSize.y - windowSize.y *
								 (timePassedInSec / introMovementTimInSec) + yPos - 10);
	}

	else if (timePassedInSec > introMovementTimInSec * 2.0f)
	{
		float decimal = timePassedInSec - static_cast<int>(timePassedInSec);

		spaceSprite.setPosition(spaceSprite.getPosition().x, yPos);
		craftSprite.setPosition(craftSprite.getPosition().x, yPos);
		rocketSprite.setPosition(rocketSprite.getPosition().x, yPos - 10);

		if (decimal < 0.5f)
		{
			pressEnterText.setScale(1.0f, 1.0f);
		}
		else
		{
			pressEnterText.setScale(0.0f, 0.0f);
		}
	}

	timePassedInSec += time.asSeconds();
}

void StateIntro::draw()
{
	auto window = stateManager->getContext()->window->getRenderWindow();
	window->draw(spaceSprite);
	window->draw(rocketSprite);
	window->draw(craftSprite);
	window->draw(madeByText);
	window->draw(pressEnterText);
}

void StateIntro::skip(EventDetails* details)
{
	if (stateManager->getContext()->shaderManager->areShadersCompiled())
	{
		//stateManager->switchTo(StateType::MainMenu);
		stateManager->switchTo(StateType::SimulationLoading);
		stateManager->remove(StateType::Intro);
	}
}
