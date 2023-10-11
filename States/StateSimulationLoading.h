#pragma once

#include "AppFramework/StateManager/StateManager.h"
#include "AppFramework/StateManager/BaseState.h"

class StateSimulationLoading : public BaseState
{
public:
	StateSimulationLoading(StateManager* stateManager, Render render = Render::twoDimensional);

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

private:
	sf::Color firstBackgroundColor;
	sf::Time timePassed;
	float animationTimeInSec;
};

