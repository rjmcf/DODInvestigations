#pragma once

#include "enemy.hpp"

#include <memory>
#include <vector>

class EnemyBatch
{
public:
    void setEnemies(std::vector<std::unique_ptr<Enemy>>&& inEnemies)
    {
        allEnemies = std::move(inEnemies);
    }

    void update(int deltaTimeMs) const;
    void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;

    void kill();

    bool isAlive() const { return bIsAlive; }
    int getNumEnemies() const { return allEnemies.size(); }

private:
    std::vector<std::unique_ptr<Enemy>> allEnemies;
    bool bIsAlive = true;
};
