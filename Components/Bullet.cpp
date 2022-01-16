#include "Bullet.h"
#include "../Game/GameObject.h"

void Bullet::execute(char curTick)
{
    if (parent->getPosition().getY() <= 0)
        parent->markedForDelete = true;
}

void Bullet::exitCleanly()
{

}

void Bullet::onCollision(GameObject *gl, GameObject *gr)
{
    gl->markedForDelete = true;
    gr->markedForDelete = true;
}
