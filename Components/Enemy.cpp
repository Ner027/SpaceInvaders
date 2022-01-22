#include "Enemy.h"

void Enemy::exitCleanly()
{
    //Quando for destruido, adicionar a score correspondente a este inimigo
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
    //Ao colidir com algo destruir esse objecto
    gr->markedForDelete = true;
    //Se for o jogador, acabar o nivel
    if (gr->getId() == gm->getPlayerId())
        gm->endCurrentLevel();

}

