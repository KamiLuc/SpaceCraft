#pragma once

#include "../AppFramework/StateManager/StateManager.h"
#include "../AppFramework/StateManager/BaseState.h"

class StateSpaceSimulation : public BaseState
{
private:
	using BaseState::BaseState;

public:

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;
};