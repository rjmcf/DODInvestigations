#pragma once

#include "eventListener.hpp"

class Colour;
class EventManager;

class BgColourEventListener : public EventListener
{
public:
    void setUp(Colour* inColour);
private:
    // ~Begin EventListener
    virtual void onEventTriggered(const std::string& eventName) override;
    // ~End EventListener

    Colour* bgColour = nullptr;
};
