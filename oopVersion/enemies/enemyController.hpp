#pragma once

#include "drawCall.hpp"
#include "enemyBatch.hpp"
#include "events/eventListener.hpp"

#include <memory>
#include <vector>

class AttachmentSpear;

class EnemyController : public EventListener
{
public:
    void addEnemies(std::vector<EnemyBatch>&& newEnemyBatches);
    void addSpears(std::vector<AttachmentSpear*>&& newSpears);
    void update(int deltaTimeMs) const;
    void drawAllEnemies(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;
    void killHalfEnemies();
    void enemyAttack() const;

    void reportEnemyNumber() const;

private:
    // ~Begin EventListener
    virtual void onEventTriggered(const std::string& eventName) override;
    // ~End EventListener

    std::vector<EnemyBatch> allEnemyBatches;
    std::vector<AttachmentSpear*> allSpears;
};
