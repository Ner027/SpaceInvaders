#ifndef SPACEINVADERS_ENEMYROW_H
#define SPACEINVADERS_ENEMYROW_H
#include <vector>
#include "../Game/GameObject.h"

using namespace std;
class EnemyRow : public IComponent
{
private:
    vector<GameObject*> enemies;
    Vector2 localPosition;
    Vector2 currentDirection = Vector2::Zero();
    GameObject* parent;
    friend class GameObject;
public:
    EnemyRow(const Vector2& startPosition,const string& name,short enCount);
    void exitCleanly() override;
    void execute(char curTick) override;
    [[nodiscard]] std::string getName() const override {return "EnemyRow";}
};


#endif
