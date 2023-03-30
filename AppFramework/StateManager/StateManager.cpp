#include "StateManager.h"
#include "../../States/StateIntro.h"
#include "../../States/StateMainMenu.h"

StateManager::StateManager(SharedContext* sharedContext) : sharedContext(sharedContext)
{
	this->registerState<StateIntro>(StateType::Intro);
	this->registerState<StateMainMenu>(StateType::MainMenu);
	//this->registerState<State_Game>(StateType::Game);
	//this->registerState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
	for (auto& state : this->states)
	{
		state.second->onDestroy();
		delete state.second;
	}
}

void StateManager::update(const sf::Time& time)
{
	if (this->states.empty()) { return; }
	if (this->states.back().second->isTranscendent() && this->states.size() > 1)
	{
		auto statesIt = this->states.end();
		while (statesIt != this->states.begin())
		{
			if (statesIt != this->states.end())
			{
				if (!statesIt->second->isTranscendent())
				{
					break;
				}
			}
			--statesIt;
		}
		for (; statesIt != this->states.end(); ++statesIt)
		{
			statesIt->second->update(time);
		}
	}
	else
	{
		this->states.back().second->update(time);
	}
}

void StateManager::draw()
{
	if (this->states.empty())
	{
		return;
	}
	if (this->states.back().second->isTransparent() && this->states.size() > 1)
	{
		auto stateIt = this->states.end();
		while (stateIt != this->states.begin())
		{
			if (stateIt != this->states.end())
			{
				if (!stateIt->second->isTransparent())
				{
					break;
				}
			}
			--stateIt;
		}
		for (; stateIt != this->states.end(); ++stateIt)
		{
			stateIt->second->draw();
		}
	}
	else
	{
		this->states.back().second->draw();
	}
}

void StateManager::processRequest()
{
	while (this->statesToRemove.begin() != this->statesToRemove.end())
	{
		this->removeState(*statesToRemove.begin());
		this->statesToRemove.erase(this->statesToRemove.begin());
	}
}

SharedContext* StateManager::getContext()
{
	return this->sharedContext;
}

bool StateManager::hasState(const StateType& type) const
{
	for (auto it = this->states.begin(); it != this->states.end(); ++it)
	{
		if (it->first == type)
		{
			auto removed = std::find(this->statesToRemove.begin(), this->statesToRemove.end(), type);
			return removed == this->statesToRemove.end() ? true : false;
		}
		return false;
	}
}

void StateManager::switchTo(const StateType& type)
{
	this->sharedContext->eventManager->setCurrentState(type);

	for (auto it = this->states.begin(); it != this->states.end(); ++it)
	{
		if (it->first == type)
		{
			this->states.back().second->deactivate();
			auto tempType = it->first;
			auto& tempState = it->second;
			this->states.erase(it);
			this->states.emplace_back(tempType, tempState);
			tempState->activate();
			return;
		}
	}

	if (!this->states.empty())
	{
		this->states.back().second->deactivate();
	}

	this->createState(type);
	this->states.back().second->activate();
}

void StateManager::createState(const StateType& type)
{
	auto newState = this->stateFactory.find(type);
	if (newState == this->stateFactory.end())
	{
		return;
	}
	auto state = newState->second();
	this->states.emplace_back(type, state);
	state->onCreate();
}

void StateManager::removeState(const StateType& type)
{
	for (auto it = this->states.begin(); it != this->states.end(); ++it)
	{
		if (it->first == type)
		{
			it->second->onDestroy();
			delete it->second;
			this->states.erase(it);
			return;
		}
	}
}

void StateManager::remove(const StateType& type)
{
	this->statesToRemove.push_back(type);
}
