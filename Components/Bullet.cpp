#include "Bullet.h"
#include "../Game/GameObject.h"
#include "../Components/Enemy.h"
#include "../Managers/GameManager.h"

void Bullet::execute(char curTick) {}

void Bullet::exitCleanly()
{
    GameManager* gm = GameManager::getInstance();
    if (parent->getId() == gm->getPlayerId())
        gm->playerCanFire = true;
    else gm->enemyCanFire = true;
}

void Bullet::onCollision(GameObject *gl, GameObject *gr)
{
    if (gl->getId() == parent->getId())
        return;
    gl->markedForDelete = true;
    gr->markedForDelete = true;
}

void Bullet::onAdd() {}

Bullet::Bullet(GameObject* parent)
{
    this->parent = parent;
}

