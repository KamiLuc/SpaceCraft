#pragma once

#include <SFML/System.hpp>

class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* stateManager, bool render3D = false) : stateManager(stateManager), transparent(false), transcendent(false), render3D(render3D) {}
	virtual ~BaseState() {}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& time) = 0;
	virtual void draw() = 0;

	void setTransparent(bool transparent) { this->transparent = transparent; }
	void setTranscendent(bool transcendent) { this->transcendent = transcendent; }

	bool shouldRender3D() const { return this->render3D; }
	bool isTransparent() const { return this->transparent; }
	bool isTranscendent() const { return this->transcendent; }
	StateManager* getStateManager() { return this->stateManager; }

protected:
	StateManager* stateManager;
	bool transparent;
	bool transcendent;
	bool render3D;
};

