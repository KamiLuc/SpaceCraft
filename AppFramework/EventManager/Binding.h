#pragma once

#include "EventType.h"
#include "EventInfo.h"
#include "EventDetails.h"

#include <vector>

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding {
	Binding(const std::string& name)
		: name(name), details(name), eventsHappening(0)
	{
	}
	void BindEvent(EventType eventType, EventInfo eventInfo = EventInfo())
	{
		events.emplace_back(eventType, eventInfo);
	}

	Events events;
	EventDetails details;
	std::string name;
	int eventsHappening;
};