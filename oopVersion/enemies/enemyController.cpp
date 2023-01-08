#include "enemyController.hpp"

void EnemyController::addEnemy(std::unique_ptr<Enemy>&& newEnemy)
{
    allAliveEnemies.push_back(std::move(newEnemy));
}

void EnemyController::update(int deltaTimeMs)
{
    for (const std::unique_ptr<Enemy>& enemyPtr : allAliveEnemies)
    {
        enemyPtr->update(deltaTimeMs);
    }
}
    
void EnemyController::drawAllEnemies(SDL_Renderer& renderer)
{
    for (const std::unique_ptr<Enemy>& enemyPtr : allAliveEnemies)
    {
        enemyPtr->draw(renderer);
    }
}