#include "TextWithBackdrop.h"

TextWithBackdrop::TextWithBackdrop(const std::string& content, const sf::Font& font, const unsigned int& characterSize,
	const sf::Color& contentColor, const sf::Color& backdropColor)
	: sf::Text(content, font, characterSize), backdrop()
{
	this->setFillColor(contentColor);
	this->setOutlineColor(contentColor);;
	this->backdrop.setFillColor(backdropColor);
	this->backdrop.setOutlineColor(backdropColor);

	sf::Vector2f center(this->getLocalBounds().width / 2.0f, this->getLocalBounds().height / 2.0f);
	sf::Vector2f localBounds(center.x + this->getLocalBounds().left, center.y + this->getLocalBounds().top);
	this->setOrigin(localBounds);

	this->backdrop.setSize({ this->getLocalBounds().width * 1.1f, this->getLocalBounds().height * 1.5f });

	this->backdrop.setOrigin(this->backdrop.getLocalBounds().width / 2.0f, this->backdrop.getLocalBounds().height / 2.0f);
	this->backdrop.setPosition(((sf::Text)(*this)).getPosition());
}

void TextWithBackdrop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backdrop);
	target.draw((sf::Text)*this);
}

void TextWithBackdrop::setPosition(float x, float y)
{
	sf::Text::setPosition(x, y);
	this->backdrop.setPosition(((sf::Text)(*this)).getPosition());
}

void TextWithBackdrop::setBackDropScale(const sf::Vector2f& scale)
{
	this->backdrop.setScale(scale);
}

bool TextWithBackdrop::isMouseOnText(sf::Vector2i mousePosition) const
{
	auto bounds = this->getGlobalBounds();

	if (mousePosition.x >= bounds.left &&
		mousePosition.x <= bounds.left + bounds.width &&
		mousePosition.y >= bounds.top &&
		mousePosition.y <= bounds.top + bounds.height)
	{
		return true;
	}

	return false;
}

sf::Vector2f TextWithBackdrop::getBackdropScale() const
{
	return this->backdrop.getScale();
}
