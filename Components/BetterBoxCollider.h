#ifndef SPACEINVADERS_BETTERBOXCOLLIDER_H
#define SPACEINVADERS_BETTERBOXCOLLIDER_H

#include "ICollisionTester.h"

class BetterBoxCollider : public ICollisionTester
{
    bool testCollision(GameObject *left, GameObject *right) override;
};


#endif
