#include "animationLibraryEntry.hpp"

#include "animatedObject.hpp"
#include "animationLibrary.hpp"
#include "animations/animationChain.hpp"
#include "animations/animationModifyVector.hpp"
#include "enemies/attachments/attachmentSpear.hpp"

#include <iostream>

std::unique_ptr<AnimationBase> AnimationLibraryEntry_Spear::getNamedAnimation(AnimatedObject& object, const std::string& animName)
{
    if (object.getAnimatedObjectId() != AttachmentSpear::name)
    {
        std::cerr << "AnimationLibraryEntry_Spear can only be used with Spears, got " << object.getAnimatedObjectId() << "instead\n";
        return nullptr;
    }

    AttachmentSpear& spear = static_cast<AttachmentSpear&>(object);

    if (animName == AnimationLibrary::attackAnimName)
    {
        std::vector<std::unique_ptr<AnimationBase>> animations;
        
        std::unique_ptr<AnimationModifyVector> prepare  = std::make_unique<AnimationModifyVector>(200, Vector{0, -5}, spear, false);
        animations.emplace_back(std::move(prepare));
        std::unique_ptr<AnimationModifyVector> moveDown = std::make_unique<AnimationModifyVector>(100, Vector{0, 20}, spear, false);
        animations.emplace_back(std::move(moveDown));
        std::unique_ptr<AnimationModifyVector> moveUp   = std::make_unique<AnimationModifyVector>(400, Vector{0,-15}, spear, false);
        animations.emplace_back(std::move(moveUp));

        return std::make_unique<AnimationChain>(std::move(animations));
    }

    std::cerr << "AnimationLibraryEntry_Spear does not define an animation for " << animName << "\n";
    return nullptr;
}