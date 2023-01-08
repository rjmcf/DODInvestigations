#pragma once

#include <string>

class EventListener
{
public:
    virtual void onEventTriggered(const std::string& eventName) = 0;
};
