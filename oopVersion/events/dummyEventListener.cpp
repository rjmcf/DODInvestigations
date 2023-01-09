#include "dummyEventListener.hpp"

#include "eventManager.hpp"

#include <iostream>

const std::string eventToListenFor = "normalEnemiesMovedHalfWay";

void DummyEventListener::setUp()
{
    EventManager::getInstance().listenToEvent(*this, eventToListenFor);
}

void DummyEventListener::onEventTriggered(const std::string& eventName)
{
    if (eventName == eventToListenFor)
    {
        std::cout << "Normal Enemies Moved HalfWay!\n";
    }
}