#include "animationLibrary.hpp"

#include "animationId.hpp"
#include "animations/animationController.hpp"
#include "enemies/attachments/attachmentSpear.hpp"
#include "utils/world.hpp"

#include <iostream>

AnimationLibrary::AnimationLibrary()
{
    library.emplace(AnimatedObjectType::Spear, std::make_unique<AnimationLibraryEntry_Spear>());
}

std::unique_ptr<AnimationBase> AnimationLibrary::getNamedAnimationFor(AnimatedObject& object, const AnimationId& animationId)
{
    auto it = library.find(object.getAnimatedObjectType());
    if (it == library.end())
    {
        std::cerr << "No animations registered for animatedObjectType: " << int(object.getAnimatedObjectType()) << "\n";
        return nullptr;
    }

    return it->second->getNamedAnimation(object, animationId);
}

void AnimationLibrary::startNamedAnimationFor(AnimatedObject& object, const AnimationId& animationId)
{
    if (std::unique_ptr<AnimationBase> foundAnim = getNamedAnimationFor(object, animationId))
    {
        World::getAnimationController().addAnimation(std::move(foundAnim));
    }
    else
    {
        std::cerr << "Could not start animation with id: " << int(animationId) << " for " << object.getAnimatedObjectId() << "\n";
    }
}