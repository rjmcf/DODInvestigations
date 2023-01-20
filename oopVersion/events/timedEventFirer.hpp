#pragma once

#include "eventManager.hpp"
#include "eventType.hpp"

#include <string>
#include <vector>

struct TimedEvent
{
    int timeToFireMs = -1;
    EventType eventToFire;
};

class TimedEventFirer
{
public:
    void setUpEvents(std::vector<TimedEvent>&& inEvents);
    void addEvent(TimedEvent&& inEvent);

protected:
    void fireEventsForTime(int timeMs);
    void resetAllEvents();

private:
    struct TimedEventInternal
    {
        TimedEvent event;
        bool bFired = false;
    };

    std::vector<TimedEventInternal> timedEvents;
};
