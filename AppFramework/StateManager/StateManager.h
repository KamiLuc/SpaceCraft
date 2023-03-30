#pragma once

#include "StateType.h"
#include "BaseState.h"
#include "../SharedContext.h"

#include <vector>
#include <unordered_map>
#include <functional>


using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void update(const sf::Time& time);
	void draw();

	void processRequest();

	SharedContext* getContext();
	bool hasState(const StateType& type) const;

	void switchTo(const StateType& type);
	void remove(const StateType& type);
	
private:
	
	void createState(const StateType& type);
	void removeState(const StateType& type);

	template<class T>
	void registerState(const StateType& type);

	SharedContext* sharedContext;
	StateContainer states;
	TypeContainer statesToRemove;
	StateFactory stateFactory;
};

template<class T>
inline void StateManager::registerState(const StateType& type)
{
	this->stateFactory[type] = [this]() -> BaseState*
	{
		return new T(this);
	};
}
