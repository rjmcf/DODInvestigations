#include "enemyBatch.hpp"

void EnemyBatch::update(int deltaTimeMs) const
{
    for (const std::unique_ptr<Enemy>& enemyPtr : allEnemies)
    {
        enemyPtr->update(deltaTimeMs);
    }
}

void EnemyBatch::draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const
{
    std::vector<std::unique_ptr<const DrawCall>> fakeDraws;
    for (unsigned int i = 0; i < allEnemies.size(); i++)
    {
        if (i % 10 == 0)
        {
            allEnemies[i]->draw(drawCalls);
        }
        else
        {
            allEnemies[i]->draw(fakeDraws);
        }
    }
}

void EnemyBatch::kill()
{
    bIsAlive = false;
    for (const std::unique_ptr<Enemy>& enemyPtr : allEnemies)
    {
        enemyPtr->kill();
    }
}
