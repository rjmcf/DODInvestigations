#include "animatedObject.hpp"

#include "animations/animationController.hpp"
#include "utils/world.hpp"

AnimatedObject::AnimatedObject()
{
    World::getAnimationController().registerAnimatedObject(*this);
}