#include "Enemy.h"
#include "../Managers/GameManager.h"

void Enemy::exitCleanly()
{
    GameManager::getInstance()->addScore(this->score);
}

void Enemy::execute(char curTick) {}

Enemy::Enemy(int score)
{
    this->score = score;
}

void Enemy::onAdd() {}

void Enemy::onCollision(GameObject *gl, GameObject *gr)
{
    GameManager* gm = GameManager::getInstance();
    gr->markedForDelete = true;
    if (gr->getId() == gm->getPlayerId())
        gm->endCurrentLevel();

}

