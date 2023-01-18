#pragma once

class AnimationController;
class EnemyController;
class EventManager;

class Globals
{
public:
    static AnimationController& getAnimationController() { return *animationController; }
    static EnemyController& getEnemyController() { return *enemyController; }
    static EventManager& getEventManager() { return *eventManager; }

private:
    friend class Application;

    static AnimationController* animationController;
    static EnemyController* enemyController;
    static EventManager* eventManager;
};
