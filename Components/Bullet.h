#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "IComponent.h"
#include "ICollider.h"

class Bullet : public IComponent , public ICollider
{
private:
public:
    void exitCleanly() override;
    void execute(char curTick) override;
    void onCollision(GameObject *gl, GameObject *gr) override;
    GameObject* parent;
    [[nodiscard]] std::string getName() const override{return "Bullet";}
};


#endif
