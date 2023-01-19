#pragma once

#include <memory>

class AnimationController;
class EnemyController;
class EventManager;

class World
{
public:
    static void setUp();
    static void tearDown();

    static AnimationController& getAnimationController() { return *getInstance().animationController.get(); }
    static EnemyController& getEnemyController() { return *getInstance().enemyController.get(); }
    static EventManager& getEventManager() { return *getInstance().eventManager.get(); }

private:
    World() = default;

    static World& getInstance();
    static std::unique_ptr<World> instance;

    std::unique_ptr<AnimationController> animationController;
    std::unique_ptr<EnemyController> enemyController;
    std::unique_ptr<EventManager> eventManager;
};
