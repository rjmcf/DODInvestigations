#include "scene.hpp"

#include "animations/animationChain.hpp"
#include "animations/animationColour.hpp"
#include "animations/animationDeform.hpp"
#include "animations/animationHealth.hpp"
#include "animations/animationTranslate.hpp"
#include "animations/animationController.hpp"
#include "enemies/attachments/attachmentShield.hpp"
#include "enemies/enemyController.hpp"
#include "enemies/enemyWithHealth.hpp"

#include "programConfig.h"
#if PROFILING
    #include "Tracy.hpp"
#endif // PROFILING

const std::string Scene::translationCompleteEventName = "TranslationComplete";

void Scene::setUp(EnemyController& enemyController, AnimationController& animationController)
{
#if PROFILING
    ZoneScopedN("Scene set up");
#endif // PROFILING

    const int duplicates = 35;

    // Normal Enemies
    {
        std::vector<std::unique_ptr<Enemy>> normalEnemies;
        std::vector<RectHaverInterface*> normalRectHavers;

        const int initialX = 80;
        const int initialY = 130;
        const int radius = 15;
        const int buffer = 2*radius + 15;
        const Vector shieldSize{10,12};
        const Vector shieldOffset{6,6};

        int tracker = 0;
        for (int copyNum = 0; copyNum < duplicates; copyNum++)
        {
            for (int column = 0; column < 30; column++)
            {
                for (int row = 0; row < 15; row++)
                {
                    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>
                    (
                        initialX + column * buffer, 
                        initialY + row * buffer,
                        radius,
                        radius,
                        Colour{0,0,255,255}
                    );

                    if (tracker % 4 == 0)
                    {
                        animationController.addAnimation(std::make_unique<AnimationColour>(2000, Colour{0,255,0,255}, *enemy.get()));
                    }
                    else if (tracker % 4 == 2)
                    {
                        animationController.addAnimation(std::make_unique<AnimationColour>(2000, Colour{0,255,255,255}, *enemy.get()));
                    }

                    if (tracker % 3 == 0)
                    {
                        std::unique_ptr<AttachmentShield> shield = std::make_unique<AttachmentShield>(shieldSize);
                        enemy->attach(std::move(shield), shieldOffset);
                    }

                    normalRectHavers.push_back(enemy.get());
                    normalEnemies.emplace_back(std::move(enemy));

                    tracker++;
                }
            }
            tracker = 0;
        }

        std::vector<std::unique_ptr<Animation>> normalTranslations;
        normalTranslations.emplace_back(new AnimationTranslate(1000, Vector{  0,  100}, normalRectHavers, true, std::make_unique<EaseIn2Out2>()));
        normalTranslations.emplace_back(new AnimationTranslate(1000, Vector{ 150,   0}, normalRectHavers, true, std::make_unique<EaseIn2Out2>()));
        normalTranslations.emplace_back(new AnimationTranslate(1000, Vector{  0, -100}, normalRectHavers, true, std::make_unique<EaseIn2Out2>()));
        normalTranslations.emplace_back(new AnimationTranslate(1000, Vector{-150,   0}, normalRectHavers, true, std::make_unique<EaseIn2Out2>()));

        for (const std::unique_ptr<Animation>& animation : normalTranslations)
        {
            animation->setUpEvents(std::vector<TimedEvent>{TimedEvent{1000, Scene::translationCompleteEventName}});
        }

        animationController.addAnimation(std::make_unique<AnimationChain>(std::move(normalTranslations)));

        enemyController.addEnemies(std::move(normalEnemies));
    }

    // Boss Enemies
    {
        std::vector<std::unique_ptr<Enemy>> bossEnemies;

        const int initialX = 80;
        const int initialY = 60;
        const int smallRadius = 30;
        const int bigRadius = 45;
        const int buffer = 2*bigRadius + 30;

        int tracker = 0;
        for (int copyNum = 0; copyNum < duplicates; copyNum++)
        {
            for (int column = 0; column < 13; column++)
            {
                for (int row = 0; row < 1; row++)
                {
                    std::unique_ptr<EnemyWithHealth> enemy = std::make_unique<EnemyWithHealth>
                    (
                        initialX + column * buffer, 
                        initialY + row * buffer,
                        smallRadius,
                        smallRadius,
                        Colour{255,0,0,255},
                        200
                    );

                    if (tracker % 2 == 0)
                    {
                        animationController.addAnimation(std::make_unique<AnimationHealth>(1500, 100, *enemy.get()));
                    }

                    std::vector<std::unique_ptr<Animation>> bossSizeAnimations;
                    bossSizeAnimations.emplace_back(new AnimationDeform(1500, Vector{bigRadius,bigRadius}, *enemy.get(), true, std::make_unique<EaseIn2Out2>()));
                    bossSizeAnimations.emplace_back(new AnimationDeform(1500, Vector{smallRadius,smallRadius}, *enemy.get(), true, std::make_unique<EaseIn2Out2>()));
                    animationController.addAnimation(std::make_unique<AnimationChain>(std::move(bossSizeAnimations)));

                    animationController.addAnimation(std::make_unique<AnimationColour>(3000, Colour{255,0,255,255}, *enemy.get()));

                    bossEnemies.emplace_back(std::move(enemy));

                    tracker++;
                }
            }
            tracker = 0;
        }

        enemyController.addEnemies(std::move(bossEnemies));
    }

    enemyController.reportEnemyNumber();
    animationController.reportStatistics();
}
