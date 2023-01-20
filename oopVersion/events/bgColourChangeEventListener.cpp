#include "bgColourChangeEventListener.hpp"

#include "colour.hpp"
#include "eventManager.hpp"
#include "scene/scene.hpp"
#include "utils/world.hpp"

void BgColourEventListener::setUp(Colour* inColour)
{
    bgColour = inColour;
    World::getEventManager().listenToEvent(*this, EventType::EnemyMoveComplete);
}

void BgColourEventListener::onEventTriggered(const EventType& event)
{
    if (event == EventType::EnemyMoveComplete)
    {
        if (bgColour)
        {
            const int oldRed = bgColour->red;
            bgColour->red = bgColour->blue;
            bgColour->blue = bgColour->green;
            bgColour->green = oldRed;
        }
    }
}