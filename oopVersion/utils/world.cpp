#include "world.hpp"

#include "animations/animationController.hpp"
#include "animations/animationLibrary/animationLibrary.hpp"
#include "enemies/enemyController.hpp"
#include "events/eventManager.hpp"

#include <iostream>

std::unique_ptr<World> World::instance;

void World::setUp()
{
    instance = std::unique_ptr<World>(new World());

    instance->animationController = std::make_unique<AnimationController>();
    instance->animationLibrary = std::make_unique<AnimationLibrary>();
    instance->eventManager = std::make_unique<EventManager>();
    
    instance->enemyController = std::make_unique<EnemyController>(*instance->eventManager.get());
}

void World::tearDown()
{
    instance.reset();
}

World& World::getInstance()
{
    if (!instance)
    {
        std::cerr << "Instance is invalid, crash expected";
    }

    return *instance.get();
}
