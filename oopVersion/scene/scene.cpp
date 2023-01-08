#include "scene.hpp"

#include "oopVersion/animations/animationColour.hpp"
#include "oopVersion/animations/animationDeform.hpp"
#include "oopVersion/animations/animationTranslate.hpp"
#include "oopVersion/animations/animationController.hpp"
#include "oopVersion/enemies/enemyController.hpp"
#include "oopVersion/enemies/enemyWithHealth.hpp"

void Scene::setUp(EnemyController& enemyController, AnimationController& animationController)
{
    std::unique_ptr<Enemy> normalEnemy1 = std::make_unique<Enemy>(30,100, 20,20, Colour{0, 0, 255, 255});
    std::unique_ptr<Enemy> normalEnemy2 = std::make_unique<Enemy>(60,100, 20,20, Colour{0, 0, 255, 255});
    std::unique_ptr<Enemy> normalEnemy3 = std::make_unique<Enemy>(90,100, 20,20, Colour{0, 0, 255, 255});
    
    std::unique_ptr<Animation> normalEnemyAnimation = std::make_unique<AnimationTranslate>(3000, Vector{0,100}, std::vector<RectHaverInterface*>{normalEnemy1.get(), normalEnemy2.get(), normalEnemy3.get()}, std::make_unique<EaseIn2Out2>());
    animationController.addAnimation(std::move(normalEnemyAnimation));

    enemyController.addEnemy(std::move(normalEnemy1));
    enemyController.addEnemy(std::move(normalEnemy2));
    enemyController.addEnemy(std::move(normalEnemy3));
    

    std::unique_ptr<Enemy> bossEnemy = std::make_unique<EnemyWithHealth>(45,30, 50,50, Colour{255, 0, 0, 255}, 200);

    std::unique_ptr<Animation> bossColourAnimation = std::make_unique<AnimationColour>(2000, Colour{255,0,255,255}, *bossEnemy.get(), std::make_unique<EaseIn2Out2>());
    animationController.addAnimation(std::move(bossColourAnimation));
    std::unique_ptr<Animation> bossSizeAnimation = std::make_unique<AnimationDeform>(2000, Vector{60,60}, *bossEnemy.get(), std::make_unique<EaseIn2Out2>());
    animationController.addAnimation(std::move(bossSizeAnimation));

    enemyController.addEnemy(std::move(bossEnemy));
}
