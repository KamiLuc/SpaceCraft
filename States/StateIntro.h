#pragma once
#include "../AppFramework/EventManager/EventDetails.h"
#include <SFML/Graphics.hpp>

class StateIntro : public BaseState
{
public:
	// Inherited via BaseState
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

	void skip(EventDetails * details);

private:
	sf::Texture introTexture;
	sf::Sprite introSprite;
	sf::Text text;
	float timePassed;
};

