#pragma once

#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Binding.h"


using CallbacksContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbacksContainer>;
using Bindings = std::unordered_map<std::string, std::shared_ptr<Binding>>;


class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBinding(std::shared_ptr<Binding> binding);
	bool removeBinding(std::string bindingName);
	void setFocus(bool focus);
	void setCurrentState(const StateType& state);

	template<class T>
	bool addCallback(StateType state, const std::string& callbackName, void(T::* function)(EventDetails*), T* instance)
	{
		auto it = this->callbacks.emplace(state, CallbacksContainer()).first;
		auto temp = std::bind(function, instance, std::placeholders::_1);
		return it->second.emplace(callbackName, temp).second;
	}

	bool removeCallback(StateType state, const std::string& callbackName);
	void handleEvent(sf::Event& event);
	void update();

	sf::Vector2i getMousePosition(sf::RenderWindow* window = nullptr);

private:
	void loadBindings();

	Bindings bindings;
	Callbacks callbacks;
	StateType currentState;
	bool focus;
};

