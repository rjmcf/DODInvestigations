#pragma once

#include "enemy.hpp"

#include <memory>
#include <vector>

class EnemyController
{
public:
    void addEnemies(std::vector<std::unique_ptr<Enemy>>&& newEnemies);
    void addEnemy(std::unique_ptr<Enemy>&& newEnemy);
    void update(int deltaTimeMs);
    void drawAllEnemies(SDL_Renderer& renderer);

private:
    std::vector<std::unique_ptr<Enemy>> allAliveEnemies;
};
