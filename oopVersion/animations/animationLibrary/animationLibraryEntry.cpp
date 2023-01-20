#include "animationLibraryEntry.hpp"

#include "animatedObject.hpp"
#include "animationId.hpp"
#include "animationLibrary.hpp"
#include "animations/animationChain.hpp"
#include "animations/animationModifyVector.hpp"
#include "enemies/attachments/attachmentSpear.hpp"

#include <iostream>

std::unique_ptr<AnimationBase> AnimationLibraryEntry_Spear::getNamedAnimation(AnimatedObject& object, const AnimationId& animationId)
{
    if (object.getAnimatedObjectType() != AnimatedObjectType::Spear)
    {
        std::cerr << "AnimationLibraryEntry_Spear can only be used with Spears (" << int(AnimatedObjectType::Spear) << "), "
                  << "got type: " << int(object.getAnimatedObjectType()) << "instead\n";
        return nullptr;
    }

    AttachmentSpear& spear = static_cast<AttachmentSpear&>(object);

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

            return std::make_unique<AnimationChain>(std::move(animations));
        }
        default:
            return nullptr;
    }
}