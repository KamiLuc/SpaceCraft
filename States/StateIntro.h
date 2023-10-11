#pragma once

#include "AppFramework/EventManager/EventDetails.h"
#include "AppFramework/StateManager/BaseState.h"
#include "AppFramework/GUI/Textbox.h"
#include "AppFramework/StateManager/StateManager.h"

#include <future>
#include <SFML/Graphics.hpp>

class StateIntro : public BaseState
{
public:
	StateIntro(StateManager* stateManager, Render render = Render::twoDimensional);
	~StateIntro() {};

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

	void skip(EventDetails* details);

private:
	sf::Texture spaceTexture;
	sf::Texture craftTexture;
	sf::Texture rocketTexture;
	sf::Font font;
	sf::Sprite spaceSprite;
	sf::Sprite craftSprite;
	sf::Sprite rocketSprite;
	sf::Text pressEnterText;
	sf::Text madeByText;
	float timePassedInSec;
	float introMovementTimInSec;
};

