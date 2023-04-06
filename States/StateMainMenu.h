#pragma once

#include "../AppFramework/StateManager/BaseState.h"
#include "../AppFramework/EventManager/EventDetails.h"

#include <vector>
#include <SFML/Graphics.hpp>

class StateMainMenu : public BaseState
{
public:
	using BaseState::BaseState;

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
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPosition;
	unsigned int buttonPadding;

	std::vector<sf::RectangleShape> rectangles;
	std::vector<sf::Text> menuLabels;
};

