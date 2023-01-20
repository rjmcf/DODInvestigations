#include "animationLibrary.hpp"

#include "animationId.hpp"
#include "animations/animationController.hpp"
#include "enemies/attachments/attachmentSpear.hpp"
#include "utils/world.hpp"

#include <iostream>

AnimationLibrary::AnimationLibrary()
{
    library.emplace(AnimatedObjectType::Knife,  std::make_unique<AnimationLibraryEntry_Knife>());
    library.emplace(AnimatedObjectType::Spear,  std::make_unique<AnimationLibraryEntry_Spear>());
    library.emplace(AnimatedObjectType::Shield, std::make_unique<AnimationLibraryEntry_Shield>());
}

std::vector<std::unique_ptr<AnimationBase>> AnimationLibrary::getAnimationsForName(AnimatedObject& object, const AnimationId& animationId)
{
    auto it = library.find(object.getAnimatedObjectType());
    if (it == library.end())
    {
        std::cerr << "No animations registered for animatedObjectType: " << int(object.getAnimatedObjectType()) << "\n";
        return {};
    }

    return it->second->getAnimationsForName(object, animationId);
}

void AnimationLibrary::startNamedAnimationFor(AnimatedObject& object, const AnimationId& animationId)
{
    World::getAnimationController().addAnimations(getAnimationsForName(object, animationId));
}