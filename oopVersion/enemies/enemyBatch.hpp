#pragma once

#include <memory>
#include <vector>

class DrawCall;
class Enemy;

class EnemyBatch
{
public:
    EnemyBatch() = default;
    EnemyBatch(EnemyBatch&& other);
    ~EnemyBatch();

    void setEnemies(std::vector<std::unique_ptr<Enemy>>&& inEnemies);

    void update(int deltaTimeMs) const;
    void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const;

    void kill();

    bool isAlive() const { return bIsAlive; }
    int getNumEnemies() const { return allEnemies.size(); }

private:
    std::vector<std::unique_ptr<Enemy>> allEnemies;
    bool bIsAlive = true;
};
