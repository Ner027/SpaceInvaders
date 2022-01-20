#ifndef SPACEINVADERS_ENEMYCONTROLLER_H
#define SPACEINVADERS_ENEMYCONTROLLER_H
#include "../Game/GameObject.h"
#include <string>

using namespace std;
class EnemyController : public IComponent
{
private:
    bool hasBullet = false;
    int killCount = 0;
    Vector2 localPosition;
    Vector2 currentHeading = Vector2::Right();
    GameObject* enemies[27];
    const string enemySprName[5] = {"enemy_basic","enemy_basic","enemy_basic","enemy_basic","enemy_basic"};
    void spawnBullet(const Vector2& position);
    bool canShoot(int i,int j);
    bool isFree[27];
public:
    explicit EnemyController(const Vector2& position);
    [[nodiscard]] std::string getName() const override {return "EnemyController";};
    void execute(char curTick) override;
    void exitCleanly() override;
};

#endif
