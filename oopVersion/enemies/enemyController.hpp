#pragma once

#include "drawCall.hpp"
#include "enemyBatch.hpp"
#include "events/eventListener.hpp"

#include <memory>
#include <vector>

class AttachmentSpear;
class EventManager;

class EnemyController : public EventListener
{
public:
    EnemyController(EventManager& eventManager);

    void addEnemies(std::vector<EnemyBatch>&& newEnemyBatches);
    void update(int deltaTimeMs) const;
    void drawAllEnemies(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;
    void killHalfEnemies();

    void reportEnemyNumber() const;

private:
    // ~Begin EventListener
    virtual void onEventTriggered(const EventType& event) override;
    // ~End EventListener

    std::vector<EnemyBatch> allEnemyBatches;
};
