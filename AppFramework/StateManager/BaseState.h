#pragma once

#include <SFML/System.hpp>
#include "../Window.h"

class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* stateManager, Render render = Render::twoDimensional)
		: stateManager(stateManager)
		, transparent(false)
		, transcendent(false)
		, render(render) {}

	virtual ~BaseState() {}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& time) = 0;
	virtual void draw() = 0;

	void setTransparent(bool transparent) { this->transparent = transparent; }
	void setTranscendent(bool transcendent) { this->transcendent = transcendent; }

	Render getRender() const { return this->render; }
	bool isTransparent() const { return this->transparent; }
	bool isTranscendent() const { return this->transcendent; }
	StateManager* getStateManager() { return this->stateManager; }

protected:
	StateManager* stateManager;
	Render render;
	bool transparent;
	bool transcendent;
};

