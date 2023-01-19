#include "bgColourChangeEventListener.hpp"

#include "colour.hpp"
#include "eventManager.hpp"
#include "scene/scene.hpp"
#include "utils/world.hpp"

void BgColourEventListener::setUp(Colour* inColour)
{
    bgColour = inColour;
    World::getEventManager().listenToEvent(*this, Scene::translationCompleteEventName);
}

void BgColourEventListener::onEventTriggered(const std::string& eventName)
{
    if (eventName == Scene::translationCompleteEventName)
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