#pragma once

#include "AppFramework/StateManager/BaseState.h"
#include "AppFramework/EventManager/EventDetails.h"
#include "AppFramework/GUI/TextWithBackdrop.h"
#include "AppFramework/StateManager/StateManager.h"

#include <vector>
#include <SFML/Graphics.hpp>

class StateMainMenu : public BaseState
{
public:
	StateMainMenu(StateManager* stateManager, Render render = Render::twoDimensional);

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

	void mouseClick(EventDetails* details);

private:
	sf::Font font;
	sf::Text text;
	std::string repoUrl;
	float currentHoverAnimationTimeInSec;
	float animationTimeInSec;
	TextWithBackdrop* selectedButton;
	std::vector<TextWithBackdrop> buttons;
};

