#include "animationLibraryEntry.hpp"

#include "animatedObject.hpp"
#include "animationId.hpp"
#include "animationLibrary.hpp"
#include "animations/animationChain.hpp"
#include "animations/animationModifyVector.hpp"
#include "interfaces/rectHaverInterface.hpp"
#include "interfaces/vectorHaverInterface.hpp"

#include <iostream>

bool AnimationLibraryEntry::checkObjectIsValid(const AnimatedObject& object)
{
    if (object.getAnimatedObjectType() != getExpectedObjectType())
    {
        std::cerr << "This AnimationLibraryEntry can only be used with objects of type" << int(getExpectedObjectType()) << "), "
                  << "got type: " << int(object.getAnimatedObjectType()) << "instead\n";
        return false;
    }

    return true;
}

AnimatedObjectType AnimationLibraryEntry_Spear::getExpectedObjectType() const
{
    return AnimatedObjectType::Spear;
}

std::vector<std::unique_ptr<AnimationBase>> AnimationLibraryEntry_Spear::getAnimationsForName(AnimatedObject& object, const AnimationId& animationId)
{
    if (!checkObjectIsValid(object))
    {
        return {};
    }

    VectorHaverInterface& spear = dynamic_cast<VectorHaverInterface&>(object);

    switch (animationId)
    {
        case AnimationId::Attack:
        {
            std::vector<std::unique_ptr<AnimationBase>> animations;
            
            std::unique_ptr<AnimationModifyVector> prepare  = std::make_unique<AnimationModifyVector>(200, Vector{0, -5}, spear, false);
            animations.emplace_back(std::move(prepare));
            std::unique_ptr<AnimationModifyVector> moveDown = std::make_unique<AnimationModifyVector>(100, Vector{0, 20}, spear, false);
            animations.emplace_back(std::move(moveDown));
            std::unique_ptr<AnimationModifyVector> moveUp   = std::make_unique<AnimationModifyVector>(400, Vector{0,-15}, spear, false);
            animations.emplace_back(std::move(moveUp));

            std::vector<std::unique_ptr<AnimationBase>> result;
            result.emplace_back(std::make_unique<AnimationChain>(std::move(animations)));
            return result;
        }
        default:
            return {};
    }
}