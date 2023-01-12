#pragma once

#include <string>

class AnimationController;
class EnemyController;

class Scene
{
public:
    void setUp(EnemyController& enemyController, AnimationController& AnimationController);

    static const std::string translationCompleteEventName;
};
