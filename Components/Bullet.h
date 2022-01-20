#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "IComponent.h"
#include "ICollider.h"

class Bullet : public IComponent , public ICollider
{
private:
    bool* isAlive;
    GameObject* parent;
public:
    explicit Bullet(bool* isAlive,GameObject* parent);
    void exitCleanly() override;
    void execute(char curTick) override;
    void onCollision(GameObject *gl, GameObject *gr) override;
    [[nodiscard]] std::string getName() const override{return "Bullet";}
};


#endif
