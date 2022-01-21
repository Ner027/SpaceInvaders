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

    if (gl->getComponent("Enemy") && gr->getComponent("Enemy"))
        return;

    auto gm = GameManager::getInstance();
    long playerId = gm->getPlayerId();
    if (gr->getId() == playerId)
        gm->endCurrentLevel();

    gl->markedForDelete = true;
    gr->markedForDelete = true;
}

void Bullet::onAdd() {}

Bullet::Bullet(GameObject* parent)
{
    this->parent = parent;
}

