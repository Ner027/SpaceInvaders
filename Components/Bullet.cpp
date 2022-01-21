#include "Bullet.h"
#include "../Components/Enemy.h"
#include "../Managers/GameManager.h"

void Bullet::execute(char curTick) {}

void Bullet::exitCleanly()
{
    auto gm = GameManager::getInstance();
    if (parent->getId() == gm->getPlayerId())
        gm->playerCanFire = true;
    else gm->enemyCanFire = true;
}

void Bullet::onCollision(GameObject *gl, GameObject *gr)
{
    if (gr->getId() == parent->getId())
        return;

    auto gm = GameManager::getInstance();
    if (gr->getId() == gm->getPlayerId())
        gm->endCurrentLevel();

    gl->markedForDelete = true;
    gr->markedForDelete = true;
}

void Bullet::onAdd() {}

Bullet::Bullet(GameObject* parent)
{
    this->parent = parent;
}

