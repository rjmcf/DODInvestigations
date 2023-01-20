#include "scene.hpp"

#include "animations/animationChain.hpp"
#include "animations/animationColour.hpp"
#include "animations/animationDeform.hpp"
#include "animations/animationHealth.hpp"
#include "animations/animationTranslate.hpp"
#include "animations/animationController.hpp"
#include "enemies/attachments/attachmentKnife.hpp"
#include "enemies/attachments/attachmentShield.hpp"
#include "enemies/attachments/attachmentSpear.hpp"
#include "enemies/enemyBatch.hpp"
#include "enemies/enemyController.hpp"
#include "enemies/enemyWithHealth.hpp"
#include "utils/world.hpp"

#include "programConfig.h"
#if PROFILING
    #include "Tracy.hpp"
#endif // PROFILING

void Scene::setUp()
{
#if PROFILING
    ZoneScopedN("Scene set up");
#endif // PROFILING

    const int duplicates = 200;
    AnimationController& animationController = World::getAnimationController();
    EnemyController& enemyController = World::getEnemyController();

    // Normal Enemies
    {
        std::vector<EnemyBatch> normalEnemyBatches;
        std::vector<RectHaverInterface*> normalRectHavers;

        const int initialX = 80;
        const int initialY = 130;
        const int radius = 15;
        const int buffer = 2*radius + 15;
        const Vector knifeOffset{16,12};
        const Vector shieldSize{10,12};
        const Vector shieldOffset{6,6};
        const Vector spearOffset{-17,15};

        int tracker = 0;
        for (int column = 0; column < 30; column++)
        {
            for (int row = 0; row < 15; row++)
            {
                std::vector<std::unique_ptr<Enemy>> enemiesInBatch;
                for (int copyNum = 0; copyNum < duplicates; copyNum++)
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

                    if (tracker % 6 == 2)
                    {
                        std::unique_ptr<AttachmentShield> shield = std::make_unique<AttachmentShield>(shieldSize);
                        enemy->attach(std::move(shield), shieldOffset);
                    }

                    if (tracker % 6 == 4 || tracker % 6 == 5)
                    {
                        std::unique_ptr<AttachmentKnife> knife = std::make_unique<AttachmentKnife>();
                        enemy->attach(std::move(knife), knifeOffset);
                    }

                    if (tracker % 3 == 2)
                    {
                        std::unique_ptr<AttachmentSpear> spear = std::make_unique<AttachmentSpear>();
                        enemy->attach(std::move(spear), spearOffset);
                    }

                    normalRectHavers.push_back(enemy.get());
                    enemiesInBatch.emplace_back(std::move(enemy));
                }

                EnemyBatch batch;
                batch.setEnemies(std::move(enemiesInBatch));
                normalEnemyBatches.emplace_back(std::move(batch));
                tracker++;
            }
        }

        const int translationTime = 1000;
        const int doAnimationTime = 600;
        const int distanceDown = 100;
        const int distanceRight = 150;
        std::unique_ptr<AnimationTranslate> moveDown  = std::make_unique<AnimationTranslate>(translationTime, Vector{0, distanceDown},   normalRectHavers, true, std::make_unique<EaseIn2Out2>());
        std::unique_ptr<AnimationTranslate> moveRight = std::make_unique<AnimationTranslate>(translationTime, Vector{distanceRight, 0},  normalRectHavers, true, std::make_unique<EaseIn2Out2>());
        std::unique_ptr<AnimationTranslate> moveUp    = std::make_unique<AnimationTranslate>(translationTime, Vector{0, -distanceDown},  normalRectHavers, true, std::make_unique<EaseIn2Out2>());
        std::unique_ptr<AnimationTranslate> moveLeft  = std::make_unique<AnimationTranslate>(translationTime, Vector{-distanceRight, 0}, normalRectHavers, true, std::make_unique<EaseIn2Out2>());

        moveDown->setUpEvents(std::vector<TimedEvent>
        {
            TimedEvent{doAnimationTime, EventType::EnemyAttack}, 
            TimedEvent{translationTime, EventType::EnemyMoveComplete}
        });
        moveRight->setUpEvents(std::vector<TimedEvent>
        {
            TimedEvent{doAnimationTime, EventType::EnemyAttack}, 
            TimedEvent{translationTime, EventType::EnemyMoveComplete}
        });

        moveUp->setUpEvents(std::vector<TimedEvent>
        {
            TimedEvent{doAnimationTime, EventType::EnemyDefend}, 
            TimedEvent{translationTime, EventType::EnemyMoveComplete}
        });
        moveLeft->setUpEvents(std::vector<TimedEvent>
        {
            TimedEvent{doAnimationTime, EventType::EnemyDefend}, 
            TimedEvent{translationTime, EventType::EnemyMoveComplete}
        });

        std::vector<std::unique_ptr<AnimationBase>> baseAnimations;
        baseAnimations.emplace_back(std::move(moveDown));
        baseAnimations.emplace_back(std::move(moveRight));
        baseAnimations.emplace_back(std::move(moveUp));
        baseAnimations.emplace_back(std::move(moveLeft));

        animationController.addAnimation(std::make_unique<AnimationChain>(std::move(baseAnimations)));

        enemyController.addEnemies(std::move(normalEnemyBatches));
    }

    // Boss Enemies
    {
        std::vector<EnemyBatch> bossEnemyBatches;

        const int initialX = 80;
        const int initialY = 60;
        const int smallRadius = 30;
        const int bigRadius = 45;
        const int buffer = 2*bigRadius + 30;

        int tracker = 0;
        for (int column = 0; column < 13; column++)
        {
            for (int row = 0; row < 1; row++)
            {
                std::vector<std::unique_ptr<Enemy>> enemiesInBatch;
                for (int copyNum = 0; copyNum < duplicates; copyNum++)
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

                    std::vector<std::unique_ptr<AnimationBase>> bossSizeAnimations;
                    bossSizeAnimations.emplace_back(new AnimationDeform(1500, Vector{bigRadius,bigRadius}, *enemy.get(), true, std::make_unique<EaseIn2Out2>()));
                    bossSizeAnimations.emplace_back(new AnimationDeform(1500, Vector{smallRadius,smallRadius}, *enemy.get(), true, std::make_unique<EaseIn2Out2>()));
                    animationController.addAnimation(std::make_unique<AnimationChain>(std::move(bossSizeAnimations)));

                    animationController.addAnimation(std::make_unique<AnimationColour>(3000, Colour{255,0,255,255}, *enemy.get()));

                    enemiesInBatch.emplace_back(std::move(enemy));
                }

                EnemyBatch batch;
                batch.setEnemies(std::move(enemiesInBatch));
                bossEnemyBatches.emplace_back(std::move(batch));

                tracker++;
            }
        }

        enemyController.addEnemies(std::move(bossEnemyBatches));
    }

    enemyController.reportEnemyNumber();
    animationController.reportStatistics();
}
