#include "StateMainMenu.h"
#include "../AppFramework/StateManager/StateManager.h"

float timePassed = 0.0f;
float scale = 0.0f;

void StateMainMenu::onCreate()
{
	auto window = this->stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::White);

	unsigned int characterSize = windowSize.y / 20;

	this->font.loadFromFile("Michroma-Regular.ttf");
	this->text.setFont(this->font);

	std::vector<std::string> menuStrings = { "New simulation", "Load simulation", "Options", "Source code", "Exit" };




	for (size_t i = 0; i < menuStrings.size(); i++)
	{
		sf::Text label(menuStrings[i], this->font, characterSize);
		label.setFillColor(sf::Color::Black);
		label.setOrigin(label.getLocalBounds().width / 2, label.getLocalBounds().height);
		label.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y / 10 * (i + 1)));

		this->menuLabels.push_back(label);
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
	int speed = 6;

	scale = timePassed * speed;



	timePassed += time.asSeconds();
	if (timePassed > static_cast<float>(1) / speed)
	{
		timePassed = 0.0f;
	}
}

void StateMainMenu::draw()
{
	sf::RenderWindow* window = this->stateManager->getContext()->window->getRenderWindow();

	std::string str("HEJ HEJ HEJ");
	sf::Text text(str, this->font, 32);
	text.setFillColor(sf::Color::Black);
	auto rectangleSize = text.getGlobalBounds();
	text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().top + text.getGlobalBounds().height / 2.0f);

	sf::RectangleShape back1({ static_cast<float>(rectangleSize.width * 1.2f), static_cast<float>(rectangleSize.height * 2.8f) });

	auto cc = this->stateManager->getContext()->window->getClearColor();
	sf::Uint8 c = 90;

	back1.setFillColor({ (sf::Uint8)(cc.r + c),  (sf::Uint8)(cc.g + c),  (sf::Uint8)(cc.b + c) });
	back1.setPosition(500, 500);
	back1.setOrigin({ back1.getSize().x / 2, back1.getSize().y / 2 });
	sf::RectangleShape back2 = back1;
	back2.setFillColor(sf::Color::Blue);
	back2.setScale({ scale, 1.0f });

	text.setPosition(back1.getPosition());

	for (size_t i = 0; i < this->menuLabels.size(); i++)
	{
		window->draw(this->menuLabels.at(i));
		window->draw(back1);
		window->draw(back2);
		window->draw(text);
	}
}
