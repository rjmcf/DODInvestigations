#pragma once

#include "eventType.hpp"

#include <map>
#include <vector>

class EventListener;

class EventManager
{
public:
    void listenToEvent(EventListener& eventListener, const EventType& event);
    void listenToEvents(EventListener& eventListener, std::vector<EventType>&& events);
    void stopListeningToEvent(EventListener& eventListener, const EventType& event);

    void triggerEvent(const EventType& event) const;

private:
    std::map<EventType, std::vector<EventListener*>> eventListeners;
};
