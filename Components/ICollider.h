#ifndef SPACEINVADERS_ICOLLIDER_H
#define SPACEINVADERS_ICOLLIDER_H

class GameObject;
class ICollider
{
public:
    virtual void onCollision(GameObject* gl ,GameObject* gr) = 0;
};

#endif
