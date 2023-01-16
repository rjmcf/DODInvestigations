#pragma once

#include "drawCall.hpp"
#include "enemy.hpp"

#include <memory>
#include <vector>

class EnemyController
{
public:
    void addEnemies(std::vector<std::unique_ptr<Enemy>>&& newEnemies);
    void addEnemy(std::unique_ptr<Enemy>&& newEnemy);
    void update(int deltaTimeMs) const;
    void drawAllEnemies(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;
    void killHalfEnemies() const;

    void reportEnemyNumber() const;

private:
    std::vector<std::unique_ptr<Enemy>> allEnemies;
};
