#include "StateMainMenu.h"
#include "../AppFramework/StateManager/StateManager.h"

//to delete
#include <iostream>

float timePassed = 0.0f;
float scale = 0.0f;

void StateMainMenu::onCreate()
{
	auto window = this->stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::White);

	unsigned int characterSize = windowSize.y / 20;
	this->firstButtonPosition = sf::Vector2f(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 4.5f);
	this->buttonSize = sf::Vector2f(static_cast<GLfloat>(windowSize.x / 2.5f), static_cast<GLfloat>(characterSize * 1.6f));
	this->buttonsPadding = windowSize.y / 20;
	this->selectedButton = nullptr;

	this->font.loadFromFile("Michroma-Regular.ttf");
	this->text.setFont(this->font);

	std::vector<std::string> menuStrings = { "New simulation", "Load simulation", "Options", "Source code", "Exit" };

	for (size_t i = 0; i < menuStrings.size(); i++)
	{
		TextWithBackdrop button(menuStrings.at(i), this->font, characterSize, sf::Color::Black,
			this->buttonSize, sf::Color({ 199, 188, 187 }));

		button.setPosition(this->firstButtonPosition.x,
			this->firstButtonPosition.y + (i * (this->buttonSize.y + this->buttonsPadding)));

		button.setBackDropScale({ 0.0f, 1.0f });

		this->buttons.emplace_back(std::move(button));
	}
}

void StateMainMenu::onDestroy()
{
}

void StateMainMenu::activate()
{
}

void StateMainMenu::deactivate()
{
}

void StateMainMenu::update(const sf::Time& time)
{
	sf::RenderWindow* window = this->stateManager->getContext()->window->getRenderWindow();

	int animationSpeed = 6;
	TextWithBackdrop* newSelectedButton = nullptr;

	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i].isMouseOnText(this->stateManager->getContext()->window->getMousePosition()))
		{
			newSelectedButton = &this->buttons[i];

			if (newSelectedButton == this->selectedButton)
			{
				auto oldScale = newSelectedButton->getBackdropScale().x;
				if (oldScale <= 1.0f)
				{
					newSelectedButton->setBackDropScale({ oldScale + 0.005f, 1.0f });
				}
			}
		}
		else
		{
			this->buttons[i].setBackDropScale({ 0.0f, 1.0f });
		}
	}
	this->selectedButton = newSelectedButton;
}

void StateMainMenu::draw()
{
	sf::RenderWindow* window = this->stateManager->getContext()->window->getRenderWindow();

	for (const auto& button : this->buttons)
	{
		window->draw(button);
	}
}
