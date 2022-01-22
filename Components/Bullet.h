#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "IComponent.h"
#include "ICollider.h"
#include "../Managers/GameManager.h"

using namespace std;
class Bullet : public IComponent , public ICollider
{
private:
    GameObject* parent;
public:
    explicit Bullet(GameObject* parent);
    void exitCleanly() override;
    void execute(char curTick) override;
    void onCollision(GameObject *gl, GameObject *gr) override;
    void onAdd() override;
    [[nodiscard]] string getName() const override{return "Bullet";}
};


#endif
