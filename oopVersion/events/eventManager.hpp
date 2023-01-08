#pragma once

#include <map>
#include <string>
#include <vector>

class EventListener;

class EventManager
{
public:
    void listenToEvent(EventListener* eventListener, const std::string& eventName);
    void stopListeningToEvent(EventListener* eventListener, const std::string& eventName);

    void triggerEvent(const std::string& eventName) const;

private:
    std::map<std::string, std::vector<EventListener*>> eventListeners;
};
