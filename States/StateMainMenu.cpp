#include "StateMainMenu.h"
#include "../AppFramework/StateManager/StateManager.h"

void StateMainMenu::onCreate()
{
	auto window = this->stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::White);

	unsigned int characterSize = windowSize.y / 20;
	auto firstButtonPosition = sf::Vector2f(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 4.5f);
	auto buttonsPadding = windowSize.y / 8;
	this->selectedButton = nullptr;

	this->font.loadFromFile("Michroma-Regular.ttf");
	this->text.setFont(this->font);
	this->currentHoverAnimationTimeInSec = 0.0f;
	this->animationTimeInSec = 0.2f;
	this->repoUrl = "https://github.com/KamiLuc/SpaceCraft";

	std::vector<std::string> menuStrings = { "New simulation", "Load simulation", "Options", "Source code", "Exit" };
	auto step = 255 / (menuStrings.size() + 3);

	for (size_t i = 0; i < menuStrings.size(); i++)
	{
		auto c = static_cast<sf::Uint8>(255 - (i + 1) * step);
		TextWithBackdrop button(menuStrings.at(i), this->font, characterSize, sf::Color::Black, sf::Color({ c,c,c }));

		button.setPosition(firstButtonPosition.x, firstButtonPosition.y + (i * buttonsPadding));
		button.setBackDropScale({ 0.0f, 1.0f });

		this->buttons.emplace_back(std::move(button));
	}

	this->stateManager->getContext()->eventManager->addCallback(StateType::MainMenu, "Mouse_Left_Click", &StateMainMenu::mouseClick, this);
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

	TextWithBackdrop* newSelectedButton = nullptr;

	for (auto& button : this->buttons)
	{
		if (button.isMouseOnText(this->stateManager->getContext()->window->getMousePosition()))
		{
			newSelectedButton = &button;

			if (newSelectedButton == this->selectedButton)
			{
				this->currentHoverAnimationTimeInSec += time.asSeconds();
				auto scale = this->currentHoverAnimationTimeInSec / this->animationTimeInSec;

				if (scale >= 1.0f)
				{
					scale = 1.0f;
				}

				newSelectedButton->setBackDropScale({ scale, 1.0f });
			}
			else
			{
				this->currentHoverAnimationTimeInSec = 0.0f;
			}
		}
		else
		{
			button.setBackDropScale({ 0.0f, 1.0f });
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

void StateMainMenu::mouseClick(EventDetails* details)
{
	auto context = this->stateManager->getContext();

	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i].isMouseOnText(details->mouse))
		{
			switch (i)
			{
			case 0:
				this->getStateManager()->switchTo(StateType::SimulationLoading);
				break;
			case 3:
#ifdef _WIN32
				system((std::string("start ") + this->repoUrl).c_str());
#elif __APPLE__
				system((std::string("open ") + this->repoUrl).c_str());
#else
				system((std::string("xdg-open ") + this->repoUrl).c_str());
#endif
				break;
			case 4:
				context->window->close();
				break;
			default:
				break;
			}
		}
	}
}
