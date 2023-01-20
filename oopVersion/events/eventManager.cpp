#include "eventManager.hpp"

#include "eventListener.hpp"

#include <algorithm>

void EventManager::listenToEvent(EventListener& eventListener, const EventType& event)
{
    std::vector<EventListener*>& registeredListeners = eventListeners.insert({event, {}}).first->second;
    registeredListeners.push_back(&eventListener);
}

void EventManager::stopListeningToEvent(EventListener& eventListener, const EventType& event)
{
    auto pairIterator = eventListeners.find(event);
    if (pairIterator != eventListeners.end())
    {
        std::vector<EventListener*>& registeredListeners = pairIterator->second;
        std::remove(registeredListeners.begin(), registeredListeners.end(), &eventListener);
    }
}

void EventManager::triggerEvent(const EventType& event) const
{
    auto pairIterator = eventListeners.find(event);
    if (pairIterator != eventListeners.end())
    {
        const std::vector<EventListener*>& registeredListeners = pairIterator->second;
        for (EventListener* listener : registeredListeners)
        {
            listener->onEventTriggered(event);
        }
    }
}
