#include "animationLibraryEntry.hpp"

#include "animatedObject.hpp"
#include "animatedObjectType.hpp"
#include "animationId.hpp"
#include "animations/animationChain.hpp"
#include "animations/animationDeform.hpp"
#include "animations/animationModifyVector.hpp"
#include "animations/animationTranslate.hpp"
#include "interfaces/rectHaverInterface.hpp"
#include "interfaces/vectorHaverInterface.hpp"

#include <SDL.h>

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

// Spear
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

// Shield
AnimatedObjectType AnimationLibraryEntry_Shield::getExpectedObjectType() const
{
    return AnimatedObjectType::Shield;
}

std::vector<std::unique_ptr<AnimationBase>> AnimationLibraryEntry_Shield::getAnimationsForName(AnimatedObject& object, const AnimationId& animationId)
{
    if (!checkObjectIsValid(object))
    {
        return {};
    }

    RectHaverInterface& shield = dynamic_cast<RectHaverInterface&>(object);

    switch (animationId)
    {
        case AnimationId::Defend:
        {
            const int expandTime = 500, contractTime = 100;
            std::vector<std::unique_ptr<AnimationBase>> sizeAnimations;
            std::vector<std::unique_ptr<AnimationBase>> positionAnimations;
            const SDL_Rect originalRect = shield.getRect();
            const Vector originalSize{float(originalRect.w), float(originalRect.h)};
            const Vector translate{originalSize.x / 2, originalSize.y / 2};
            const Vector newSize{originalSize.x * 2, originalSize.y * 2};

            std::unique_ptr<AnimationDeform> expand   = std::make_unique<AnimationDeform>(  expandTime,      newSize, shield, false);
            sizeAnimations.emplace_back(std::move(expand));
            std::unique_ptr<AnimationDeform> contract = std::make_unique<AnimationDeform>(contractTime, originalSize, shield, false);
            sizeAnimations.emplace_back(std::move(contract));

            std::unique_ptr<AnimationTranslate> asExpand   = std::make_unique<AnimationTranslate>(  expandTime, translate.scale(-1), shield, false);
            positionAnimations.emplace_back(std::move(asExpand));
            std::unique_ptr<AnimationTranslate> asContract = std::make_unique<AnimationTranslate>(contractTime, translate,           shield, false);
            positionAnimations.emplace_back(std::move(asContract));

            std::vector<std::unique_ptr<AnimationBase>> results;
            results.emplace_back(std::make_unique<AnimationChain>(std::move(sizeAnimations)));
            results.emplace_back(std::make_unique<AnimationChain>(std::move(positionAnimations)));
            return results;
        }
        default:
            return {};
    }
}

// Knife
AnimatedObjectType AnimationLibraryEntry_Knife::getExpectedObjectType() const
{
    return AnimatedObjectType::Knife;
}

std::vector<std::unique_ptr<AnimationBase>> AnimationLibraryEntry_Knife::getAnimationsForName(AnimatedObject& object, const AnimationId& animationId)
{
    if (!checkObjectIsValid(object))
    {
        return {};
    }

    VectorHaverInterface& knife = dynamic_cast<VectorHaverInterface&>(object);

    switch (animationId)
    {
        case AnimationId::Attack:
        {
            std::vector<std::unique_ptr<AnimationBase>> animations;
            
            std::unique_ptr<AnimationModifyVector> moveDown1 = std::make_unique<AnimationModifyVector>(150, Vector{0, 15}, knife, false);
            animations.emplace_back(std::move(moveDown1));
            std::unique_ptr<AnimationModifyVector> moveUp1   = std::make_unique<AnimationModifyVector>(150, Vector{0,-15}, knife, false);
            animations.emplace_back(std::move(moveUp1));
            std::unique_ptr<AnimationModifyVector> moveDown2 = std::make_unique<AnimationModifyVector>(150, Vector{0, 15}, knife, false);
            animations.emplace_back(std::move(moveDown2));
            std::unique_ptr<AnimationModifyVector> moveUp2   = std::make_unique<AnimationModifyVector>(150, Vector{0,-15}, knife, false);
            animations.emplace_back(std::move(moveUp2));

            std::vector<std::unique_ptr<AnimationBase>> result;
            result.emplace_back(std::make_unique<AnimationChain>(std::move(animations)));
            return result;
        }
        default:
            return {};
    }
}
