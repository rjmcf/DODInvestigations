#pragma once

#include "drawCall.hpp"
#include "enemyBatch.hpp"

#include <memory>
#include <vector>

class AttachmentSpear;
class AnimationController;

class EnemyController
{
public:
    void addEnemies(std::vector<EnemyBatch>&& newEnemyBatches);
    void addSpears(std::vector<AttachmentSpear*>&& newSpears) { allSpears = std::move(newSpears); }
    void update(int deltaTimeMs) const;
    void drawAllEnemies(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;
    void killHalfEnemies();
    void enemyAttack(AnimationController& animationController) const;

    void reportEnemyNumber() const;

private:
    std::vector<EnemyBatch> allEnemyBatches;
    std::vector<AttachmentSpear*> allSpears;
};
