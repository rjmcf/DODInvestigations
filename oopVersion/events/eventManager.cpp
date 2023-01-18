#include "eventManager.hpp"

#include "eventListener.hpp"

#include <algorithm>

void EventManager::listenToEvent(EventListener& eventListener, const std::string& eventName)
{
    std::vector<EventListener*>& registeredListeners = eventListeners.insert({eventName, {}}).first->second;
    registeredListeners.push_back(&eventListener);
}

void EventManager::stopListeningToEvent(EventListener& eventListener, const std::string& eventName)
{
    auto pairIterator = eventListeners.find(eventName);
    if (pairIterator != eventListeners.end())
    {
        std::vector<EventListener*>& registeredListeners = pairIterator->second;
        std::remove(registeredListeners.begin(), registeredListeners.end(), &eventListener);
    }
}

void EventManager::triggerEvent(const std::string& eventName) const
{
    auto pairIterator = eventListeners.find(eventName);
    if (pairIterator != eventListeners.end())
    {
        const std::vector<EventListener*>& registeredListeners = pairIterator->second;
        for (EventListener* listener : registeredListeners)
        {
            listener->onEventTriggered(eventName);
        }
    }
}
