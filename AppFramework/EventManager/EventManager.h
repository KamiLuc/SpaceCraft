#pragma once

#include "Binding.h"

#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdio>
#include <sstream>

using CallbacksContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbacksContainer>;
using Bindings = std::unordered_map<std::string, std::shared_ptr<Binding>>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	sf::Vector2i getMousePosition(sf::RenderWindow* window = nullptr);
	bool addBinding(std::shared_ptr<Binding> binding);
	bool removeBinding(std::string bindingName);
	bool removeCallback(StateType state, const std::string& callbackName);
	void setFocus(bool focus);
	void setCurrentState(const StateType& state);
	void handleEvent(sf::Event& event);
	void update();

	template<class T>
	bool addCallback(StateType state, const std::string& callbackName, void(T::* function)(EventDetails*), T* instance)
	{
		auto it = this->callbacks.emplace(state, CallbacksContainer()).first;
		auto temp = std::bind(function, instance, std::placeholders::_1);
		return it->second.emplace(callbackName, temp).second;
	}

private:
	Bindings bindings;
	Callbacks callbacks;
	StateType currentState;
	bool focus;

	void loadBindings();
};

