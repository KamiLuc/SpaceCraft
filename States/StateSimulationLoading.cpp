#include "StateSimulationLoading.h"

StateSimulationLoading::StateSimulationLoading(StateManager* stateManager, Render render)
	: BaseState(stateManager, render)
{
}

void StateSimulationLoading::onCreate()
{
	this->firstBackgroundColor = this->stateManager->getContext()->window->getClearColor();
	this->animationTimeInSec = 0.8f;
}

void StateSimulationLoading::onDestroy()
{
}

void StateSimulationLoading::activate()
{
}

void StateSimulationLoading::deactivate()
{
}

void StateSimulationLoading::update(const sf::Time& time)
{
	auto sharedContext = this->stateManager->getContext();

	if (this->timePassed.asSeconds() >= this->animationTimeInSec)
	{
		sharedContext->textureManager->loadTextures();

		this->stateManager->switchTo(StateType::SpaceSimulation);
		this->stateManager->remove(StateType::SimulationLoading);
	}
	else
	{
		auto step = this->timePassed.asSeconds() / this->animationTimeInSec;
		auto nextBackgroundColor = sf::Color(
			this->firstBackgroundColor.r - static_cast<sf::Uint8>(this->firstBackgroundColor.r * step),
			this->firstBackgroundColor.g - static_cast<sf::Uint8>(this->firstBackgroundColor.g * step),
			this->firstBackgroundColor.b - static_cast<sf::Uint8>(this->firstBackgroundColor.b * step));

		this->stateManager->getContext()->window->setClearColor(std::move(nextBackgroundColor));
	}

	this->timePassed += time;
}

void StateSimulationLoading::draw()
{
}
