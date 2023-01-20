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
    virtual void onEventTriggered(const EventType& event) override;
    // ~End EventListener

    Colour* bgColour = nullptr;
};
