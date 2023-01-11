#include "enemyController.hpp"

#include "Tracy.hpp"

#include <iterator>

void EnemyController::addEnemies(std::vector<std::unique_ptr<Enemy>>&& newEnemies)
{
    allAliveEnemies.insert(allAliveEnemies.end(), std::make_move_iterator(newEnemies.begin()), std::make_move_iterator(newEnemies.end()));
}

void EnemyController::addEnemy(std::unique_ptr<Enemy>&& newEnemy)
{
    allAliveEnemies.emplace_back(std::move(newEnemy));
}

void EnemyController::update(int deltaTimeMs)
{
    ZoneScopedN("UpdateEnemies");
    for (const std::unique_ptr<Enemy>& enemyPtr : allAliveEnemies)
    {
        enemyPtr->update(deltaTimeMs);
    }
}
    
void EnemyController::drawAllEnemies(SDL_Renderer& renderer)
{
    ZoneScoped;
    for (const std::unique_ptr<Enemy>& enemyPtr : allAliveEnemies)
    {
        enemyPtr->draw(renderer);
    }
}