#pragma once

#include "StateType.h"
#include "BaseState.h"
#include "../SharedContext.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

using StateContainer = std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<std::unique_ptr<BaseState>(void)>>;

class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void update(const sf::Time& time);
	void draw();
	void processRequest();
	void switchTo(const StateType& type);
	void remove(const StateType& type);
	SharedContext* getContext();
	bool hasState(const StateType& type) const;

private:

	void createState(const StateType& type);
	void removeState(const StateType& type);

	template<class T>
	void registerState(const StateType& type, Render render);

	SharedContext* sharedContext;
	StateContainer states;
	TypeContainer statesToRemove;
	StateFactory stateFactory;
};

template<class T>
inline void StateManager::registerState(const StateType& type, Render render)
{
	this->stateFactory[type] = [this, render]() -> auto
		{
			return std::make_unique<T>(this, render);
		};
}
