
#include "EnemyContainer.h"

EnemyContainer::EnemyContainer(GameObject *enemy, const Vector2 &originalPosition) : originalPosition(originalPosition)
{
    this->enemy = enemy;
}


