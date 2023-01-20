#include "enemyController.hpp"

#include "animations/animationController.hpp"
#include "animations/animationLibrary/animationId.hpp"
#include "animations/animationLibrary/animationLibrary.hpp"
#include "attachments/attachmentSpear.hpp"
#include "events/eventManager.hpp"
#include "scene/scene.hpp"
#include "utils/world.hpp"

#include "programConfig.h"
#if PROFILING
    #include "Tracy.hpp"
#endif // PROFILING

#include <iostream>
#include <iterator>

EnemyController::EnemyController(EventManager& eventManager)
{
    eventManager.listenToEvents(*this, {EventType::EnemyAttack, EventType::EnemyDefend});
}

void EnemyController::addEnemies(std::vector<EnemyBatch>&& newEnemyBatches)
{
    allEnemyBatches.insert(allEnemyBatches.end(), std::make_move_iterator(newEnemyBatches.begin()), std::make_move_iterator(newEnemyBatches.end()));
}

void EnemyController::update(int deltaTimeMs) const
{
#if PROFILING
    ZoneScopedN("UpdateEnemies");
#endif // PROFILING

    for (const EnemyBatch& enemyBatch : allEnemyBatches)
    {
        enemyBatch.update(deltaTimeMs);
    }
}
    
void EnemyController::drawAllEnemies(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    std::vector<const EnemyBatch*> aliveEnemies;
    aliveEnemies.reserve(allEnemyBatches.size());

    // Draw dead enemies first, so alive ones appear on top
    for (const EnemyBatch& enemyBatch : allEnemyBatches)
    {
        if (enemyBatch.isAlive())
        {
            aliveEnemies.push_back(&enemyBatch);
        }
        else
        {
            enemyBatch.draw(drawCalls);
        }
    }

    for (const EnemyBatch* enemyBatch : aliveEnemies)
    {
        enemyBatch->draw(drawCalls);
    }
}

void EnemyController::killHalfEnemies()
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    int aliveEnemyNum = 0;
    for (EnemyBatch& enemyBatch : allEnemyBatches)
    {
        if (enemyBatch.isAlive())
        {
            if (aliveEnemyNum % 2 == 0)
            {
                enemyBatch.kill();
            }

            aliveEnemyNum++;
        }
    }
}

void EnemyController::onEventTriggered(const EventType& event)
{
    switch (event)
    {
        case EventType::EnemyAttack:
        {
            World::getAnimationController().startAnimation(AnimationId::Attack);
            break;
        }
        case EventType::EnemyDefend:
        {
            World::getAnimationController().startAnimation(AnimationId::Defend);
            break;
        }
        default:
        {
            break;
        }
    }
}

void EnemyController::reportEnemyNumber() const
{
    std::cout << "Number of EnemyBatches: " << allEnemyBatches.size() << std::endl;
    
    int totalEnemies = 0;
    for (const EnemyBatch& enemyBatch : allEnemyBatches)
    {
        totalEnemies += enemyBatch.getNumEnemies();
    }

    std::cout << "Number of Enemies: " << totalEnemies << std::endl;
}
