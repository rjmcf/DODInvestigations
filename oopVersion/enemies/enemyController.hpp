#pragma once

#include "drawCall.hpp"
#include "enemyBatch.hpp"

#include <memory>
#include <vector>

class EnemyController
{
public:
    void addEnemies(std::vector<EnemyBatch>&& newEnemyBatches);
    void update(int deltaTimeMs) const;
    void drawAllEnemies(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;
    void killHalfEnemies();

    void reportEnemyNumber() const;

private:
    std::vector<EnemyBatch> allEnemyBatches;
};
