#include "Bullet.h"
#include "../Game/GameObject.h"
#include "../Components/Enemy.h"
#include "../Util/Constants.h"

void Bullet::execute(char curTick)
{
    if (parent->getPosition().getY() <= 0)
        parent->markedForDelete = true;
    if (parent->getPosition().getY() >= GW_Y)
        parent->markedForDelete = true;

}

void Bullet::exitCleanly()
{
    *isAlive = false;
}

void Bullet::onCollision(GameObject *gl, GameObject *gr)
{
    gl->markedForDelete = true;
    gr->markedForDelete = true;
}

Bullet::Bullet(bool *isAlive, GameObject *parent)
{
    this->isAlive = isAlive;
    this->parent = parent;
}

