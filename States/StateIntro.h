#pragma once
#include "../AppFramework/EventManager/EventDetails.h"
#include "../AppFramework/StateManager/BaseState.h"
#include <SFML/Graphics.hpp>
#include "../AppFramework/GUI/Textbox.h"

class StateIntro : public BaseState
{
public:
	using BaseState::BaseState;

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
	sf::Texture pressEnterTexture;
	sf::Texture madeByTexture;
	sf::Sprite spaceSprite;
	sf::Sprite craftSprite;
	sf::Sprite rocketSprite;
	sf::Sprite pressEnterSprite;
	sf::Sprite madeBySprite;

	float timePassed;
};

