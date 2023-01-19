#include "animationLibrary.hpp"

#include "animationLibraryEntry.hpp"
#include "animations/animationController.hpp"
#include "enemies/attachments/attachmentSpear.hpp"
#include "utils/globals.hpp"

#include <iostream>

std::map<std::string, std::unique_ptr<AnimationLibraryEntry>> AnimationLibrary::library;
std::string AnimationLibrary::attackAnimName = "Attack";

void AnimationLibrary::initialise()
{
    library.emplace(AttachmentSpear::name, std::make_unique<AnimationLibraryEntry_Spear>());
}

std::unique_ptr<AnimationBase> AnimationLibrary::getNamedAnimationFor(AnimatedObject& object, const std::string& animName)
{
    auto it = library.find(object.getAnimatedObjectId());
    if (it == library.end())
    {
        std::cerr << "No animations registered for " << object.getAnimatedObjectId() << "\n";
        return nullptr;
    }

    return it->second->getNamedAnimation(object, animName);
}

void AnimationLibrary::startNamedAnimationFor(AnimatedObject& object, const std::string& animName)
{
    if (std::unique_ptr<AnimationBase> foundAnim = getNamedAnimationFor(object, animName))
    {
        AnimationController& animController = Globals::getAnimationController();
        animController.addAnimation(std::move(foundAnim));
    }
    else
    {
        std::cerr << "Could not start animation: " << animName << " for " << object.getAnimatedObjectId() << "\n";
    }
}