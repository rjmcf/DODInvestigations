#include "timedEventFirer.hpp"

#include "utils/globals.hpp"

void TimedEventFirer::setUpEvents(std::vector<TimedEvent>&& inEvents)
{
    timedEvents.clear();

    for (TimedEvent event : inEvents)
    {
        addEvent(std::move(event));
    }
}

void TimedEventFirer::addEvent(TimedEvent&& inEvent)
{
    timedEvents.emplace_back(TimedEventInternal{std::move(inEvent)});
}

void TimedEventFirer::fireEventsForTime(int timeMs)
{
    for (TimedEventInternal& event : timedEvents)
    {
        if (event.bFired)
        {
            continue;
        }

        if (timeMs >= event.event.timeToFireMs)
        {
            Globals::getEventManager().triggerEvent(event.event.eventToFire);
            event.bFired = true;
        }
    }
}

void TimedEventFirer::resetAllEvents()
{
    for (TimedEventInternal& event : timedEvents)
    {
        event.bFired = false;
    }
}