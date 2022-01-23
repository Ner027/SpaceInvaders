#include "Bullet.h"
#include "../Components/Enemy.h"

void Bullet::execute(char curTick) {}

void Bullet::exitCleanly()
{
    /*Quando o objecto da bala for destruido,verificar qual foi o objecto que a criou
     * caso tenha sido o jogador, permitir que este dispare novamente,ou então permitir
     * que o inimigo dispare novamente*/

    auto gm = GameManager::getInstance();
    if (parent->getId() == gm->getPlayerId())
        gm->playerCanFire = true;
    else gm->enemyCanFire = true;
}

void Bullet::onCollision(GameObject *gl, GameObject *gr)
{
    //Se o objecto com o qual colidiu for o objecto que a criou retornar
    if (gr->getId() == parent->getId())
        return;


    auto gm = GameManager::getInstance();
    long playerId = gm->getPlayerId();


    //Se o objecto com o qual colidiu, for o jogador
    if (gr->getId() == playerId)
        gm->endCurrentLevel();

    //Destruir ambos os objectos, a bala e o objecto com a qual colidiu
    gl->markedForDelete = true;
    gr->markedForDelete = true;
}

void Bullet::onAdd() {}

Bullet::Bullet(GameObject* parent)
{
    this->parent = parent;
}

