#pragma once

#include <string>

class EventListener
{
private:
    friend class EventManager;
    virtual void onEventTriggered(const std::string& eventName) = 0;
};
