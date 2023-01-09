#pragma once

#include "eventListener.hpp"

class EventManager;

class DummyEventListener : public EventListener
{
public:
    void setUp();
private:
    // ~Begin EventListener
    virtual void onEventTriggered(const std::string& eventName) override;
    // ~End EventListener
};
