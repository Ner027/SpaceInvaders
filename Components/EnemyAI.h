#ifndef SPACEINVADERS_ENEMYAI_H
#define SPACEINVADERS_ENEMYAI_H

#include "IComponent.h"
#include "../Game/GameObject.h"
#include "../Managers/GameManager.h"
#include <vector>
#include <queue>

using namespace std;

struct EnemyContainer
{
    GameObject* enemy;
    Vector2 position;
    EnemyContainer(GameObject* enemy,const Vector2& pos) : position(pos),enemy(enemy) {}
}typedef EnemyContainer;

class EnemyAI : public IComponent
{
private:
    vector<EnemyContainer> enemies;
    vector<string> enemyNames;
    Vector2 currentVelocity;
    Vector2 lastEnemy = Vector2(-1,-1);
    GameManager* gameManager;
    int rows = 0;
    bool isFree[27]{false};
    bool canShoot(const Vector2& position);
    void spawnBullet(const Vector2& position,GameObject* parent);
public:
    explicit EnemyAI(const vector<string>& enemyNames);
    void execute(char curTick) override;
    void exitCleanly() override;
    void onAdd() override;
    [[nodiscard]] string getName() const override {return "EnemyAI";};
};

#endif
