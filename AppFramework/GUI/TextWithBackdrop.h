#pragma once

#include "SFML/Graphics.hpp" 
#include <SFML/Window.hpp>

class TextWithBackdrop : public sf::Text
{
public:
	TextWithBackdrop(const std::string& content, const sf::Font& font, const unsigned int& characterSize,
		const sf::Color& contentColor, const sf::Color& backdropColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void setPosition(float x, float y);
	void setBackDropScale(const sf::Vector2f& scale);

	bool isMouseOnText(sf::Vector2i mousePosition) const;
	sf::Vector2f getBackdropScale() const;

private:
	sf::RectangleShape backdrop;
};

