#pragma once

enum class EventType;

class EventListener
{
private:
    friend class EventManager;
    virtual void onEventTriggered(const EventType& eventType) = 0;
};
