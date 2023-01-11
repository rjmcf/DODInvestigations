#include "enemyController.hpp"

#include "profilingConfig.h"
#if PROFILING
    #include "Tracy.hpp"
#endif // PROFILING

#include <iostream>
#include <iterator>

void EnemyController::addEnemies(std::vector<std::unique_ptr<Enemy>>&& newEnemies)
{
    allEnemies.insert(allEnemies.end(), std::make_move_iterator(newEnemies.begin()), std::make_move_iterator(newEnemies.end()));
}

void EnemyController::addEnemy(std::unique_ptr<Enemy>&& newEnemy)
{
    allEnemies.emplace_back(std::move(newEnemy));
}

void EnemyController::update(int deltaTimeMs) const
{
#if PROFILING
    ZoneScopedN("UpdateEnemies");
#endif // PROFILING

    for (const std::unique_ptr<Enemy>& enemyPtr : allEnemies)
    {
        enemyPtr->update(deltaTimeMs);
    }
}
    
void EnemyController::drawAllEnemies(SDL_Renderer& renderer) const
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    std::vector<Enemy*> aliveEnemies;
    aliveEnemies.reserve(allEnemies.size());

    // Draw dead enemies first, so alive ones appear on top
    for (const std::unique_ptr<Enemy>& enemyPtr : allEnemies)
    {
        if (enemyPtr->isAlive())
        {
            aliveEnemies.push_back(enemyPtr.get());
        }
        else
        {
            enemyPtr->draw(renderer);
        }
    }

    for (const Enemy* enemy : aliveEnemies)
    {
        enemy->draw(renderer);
    }
}

void EnemyController::killHalfEnemies() const
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    int aliveEnemyNum = 0;
    for (const std::unique_ptr<Enemy>& enemyPtr : allEnemies)
    {
        if (enemyPtr->isAlive())
        {
            if (aliveEnemyNum % 2 == 0)
            {
                enemyPtr->kill();
            }

            aliveEnemyNum++;
        }
    }
}

void EnemyController::reportEnemyNumber() const
{
    std::cout << "Number of Enemies: " << allEnemies.size() << std::endl;
}
