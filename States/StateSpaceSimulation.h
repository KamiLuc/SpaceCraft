#pragma once

#include "../AppFramework/StateManager/StateManager.h"
#include "../AppFramework/StateManager/BaseState.h"
#include "../3DRenderer/Camera/CameraManagerToSFMLFrameworkAdapter.h"

class StateSpaceSimulation : public BaseState
{
public:
	using BaseState::BaseState;

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

private:
	std::unique_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
};

