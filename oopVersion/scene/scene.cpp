#include "scene.hpp"

#include "oopVersion/enemies/enemyWithHealth.hpp"

void Scene::setUp(EnemyController& enemyController)
{
    enemyController.addEnemy(std::make_unique<Enemy>(30,100, 20,20, Colour{0, 0, 255, 255}));
    enemyController.addEnemy(std::make_unique<Enemy>(60,100, 20,20, Colour{0, 0, 255, 255}));
    enemyController.addEnemy(std::make_unique<Enemy>(90,100, 20,20, Colour{0, 0, 255, 255}));
    enemyController.addEnemy(std::make_unique<EnemyWithHealth>(45,30, 50,50, Colour{255, 0, 0, 255}, 200));
}
