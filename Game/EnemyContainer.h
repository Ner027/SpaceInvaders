#ifndef SPACEINVADERS_ENEMYCONTAINER_H
#define SPACEINVADERS_ENEMYCONTAINER_H

#include "GameObject.h"

class EnemyContainer
{
public:
    GameObject* enemy;
    Vector2 originalPosition;
    EnemyContainer(GameObject* enemy, const Vector2& originalPosition);
};

#endif
