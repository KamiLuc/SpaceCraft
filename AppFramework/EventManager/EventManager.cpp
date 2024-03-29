#include "EventManager.h"

EventManager::EventManager()
	: focus(true)
	, callbacksEnabled(true)
{
	this->loadBindings();
}

EventManager::~EventManager()
{
	for (auto& bind : this->bindings)
	{
		bind.second = nullptr;
	}
}

bool EventManager::addBinding(std::shared_ptr<Binding> binding)
{
	if (this->bindings.find(binding->name) != this->bindings.end())
	{
		return false;
	}
	else
	{
		return this->bindings.emplace(binding->name, binding).second;
	}
}

bool EventManager::removeBinding(std::string bindingName)
{
	auto it = this->bindings.find(bindingName);
	if (it == this->bindings.end())
	{
		return false;
	}
	else
	{
		it->second = nullptr;
		this->bindings.erase(it);
		return true;
	}
}

void EventManager::setFocus(bool focus)
{
	this->focus = focus;
}

void EventManager::setCurrentState(const StateType& state)
{
	this->currentState = state;
}

bool EventManager::removeCallback(StateType state, const std::string& callbackName)
{
	auto it = this->callbacks.find(state);
	if (it == this->callbacks.end())
	{
		return false;
	}

	auto it2 = it->second.find(callbackName);
	if (it2 == it->second.end())
	{
		return false;
	}

	it->second.erase(callbackName);
	return true;
}

void EventManager::enableCallbacks()
{
	callbacksEnabled = true;
}

void EventManager::disableCallbacks()
{
	callbacksEnabled = false;
}

void EventManager::handleEvent(sf::Event& event)
{
	for (auto& bindingIt : bindings)
	{
		auto& bind = bindingIt.second;
		for (auto& eventIt : bind->events)
		{
			EventType sfmlEvent = static_cast<EventType>(event.type);
			if (eventIt.first != sfmlEvent)
			{
				continue;
			}
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (eventIt.second.code == event.key.code)
				{
					if (bind->details.keyCode != -1)
					{
						bind->details.keyCode = eventIt.second.code;
					}
					++(bind->eventsHappening);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				if (eventIt.second.code == event.mouseButton.button)
				{
					bind->details.mouse.x = event.mouseButton.x;
					bind->details.mouse.y = event.mouseButton.y;
					if (bind->details.keyCode != -1)
					{
						bind->details.keyCode = eventIt.second.code;
					}
					++(bind->eventsHappening);
					break;
				}
			}
			else
			{
				if (sfmlEvent == EventType::MouseWheel)
				{
					bind->details.mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized)
				{
					bind->details.size.x = event.size.width;
					bind->details.size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
				{
					bind->details.textEntered = event.text.unicode;
				}
				else if (sfmlEvent == EventType::WindowClosed)
				{
					bind->details.clear();
				}
				++(bind->eventsHappening);
			}
		}
	}
}

void EventManager::update()
{
	if (!this->focus)
	{
		return;
	}
	for (auto& bindingIt : this->bindings)
	{
		auto& bind = bindingIt.second;
		for (auto& eventIt : bind->events)
		{
			switch (eventIt.first)
			{
				case (EventType::Keyboard):
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eventIt.second.code)))
					{
						if (bind->details.keyCode != -1)
						{
							bind->details.keyCode = eventIt.second.code;
						}
						++(bind->eventsHappening);
					}
					break;
				case (EventType::Mouse):
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eventIt.second.code)))
					{
						if (bind->details.keyCode != -1)
						{
							bind->details.keyCode = eventIt.second.code;
						}
						++(bind->eventsHappening);
					}
					break;

				default:
					break;
			}
		}

		if (bind->events.size() == bind->eventsHappening && callbacksEnabled)
		{
			auto stateCallbacks = this->callbacks.find(this->currentState);
			auto otherCallbacks = this->callbacks.find(StateType(0));

			if (stateCallbacks != this->callbacks.end())
			{
				auto callIt = stateCallbacks->second.find(bind->name);
				if (callIt != stateCallbacks->second.end())
				{
					callIt->second(&bind->details);
				}
			}

			if (otherCallbacks != this->callbacks.end())
			{
				auto callIt = otherCallbacks->second.find(bind->name);
				if (callIt != otherCallbacks->second.end())
				{
					callIt->second(&bind->details);
				}
			}
		}
		bind->eventsHappening = 0;
		bind->details.clear();
	}
}

sf::Vector2i EventManager::getMousePosition(sf::RenderWindow* window)
{
	return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
}

void EventManager::loadBindings()
{
	std::string delimeter = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open())
	{
		std::string errorMessage(", Can not open file: keys.cfg");
		errorMessage.insert(0, __func__);
		printf(errorMessage.c_str());
		throw std::runtime_error(errorMessage.c_str());
	}

	std::string line {};
	while (std::getline(bindings, line))
	{
		std::stringstream keyStream(line);
		std::string callbackName;
		keyStream >> callbackName;

		if (callbackName.empty())
		{
			continue;
		}

		auto bind = std::make_shared<Binding>(callbackName);
		while (!keyStream.eof())
		{
			std::string keyValue {};
			keyStream >> keyValue;
			int start = 0;
			size_t end = keyValue.find(delimeter);

			if (end == std::string::npos)
			{
				bind = nullptr;
				break;
			}

			EventType type = EventType(std::stoi(keyValue.substr(start, end - start)));
			int code = stoi(keyValue.substr(end + delimeter.length(), keyValue.find(delimeter, end + delimeter.length())));
			EventInfo eventInfo;
			eventInfo.code = code;

			bind->BindEvent(type, eventInfo);
		}
		if (bind != nullptr && !this->addBinding(bind))
		{
			bind = nullptr;
		}
	}
	bindings.close();
}
