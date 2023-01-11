#include "enemyController.hpp"

#include "profilingConfig.h"
#if PROFILING
    #include "Tracy.hpp"
#endif // PROFILING

#include <iostream>
#include <iterator>

void EnemyController::addEnemies(std::vector<std::unique_ptr<Enemy>>&& newEnemies)
{
    allAliveEnemies.insert(allAliveEnemies.end(), std::make_move_iterator(newEnemies.begin()), std::make_move_iterator(newEnemies.end()));
}

void EnemyController::addEnemy(std::unique_ptr<Enemy>&& newEnemy)
{
    allAliveEnemies.emplace_back(std::move(newEnemy));
}

void EnemyController::update(int deltaTimeMs) const
{
#if PROFILING
    ZoneScopedN("UpdateEnemies");
#endif // PROFILING

    for (const std::unique_ptr<Enemy>& enemyPtr : allAliveEnemies)
    {
        enemyPtr->update(deltaTimeMs);
    }
}
    
void EnemyController::drawAllEnemies(SDL_Renderer& renderer) const
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    for (const std::unique_ptr<Enemy>& enemyPtr : allAliveEnemies)
    {
        enemyPtr->draw(renderer);
    }
}

void EnemyController::reportEnemyNumber() const
{
    std::cout << "Number of Enemies: " << allAliveEnemies.size() << std::endl;
}
