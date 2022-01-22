#ifndef SPACEINVADERS_ICOLLISIONTESTER_H
#define SPACEINVADERS_ICOLLISIONTESTER_H

#include "../Game/GameObject.h"

class ICollisionTester
{
public:
    virtual bool testCollision(GameObject* left,GameObject* right) = 0;
    virtual ~ICollisionTester() = default;
};
#endif
