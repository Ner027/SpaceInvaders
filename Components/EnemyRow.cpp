
#include "EnemyRow.h"
#include "../Managers/AssetManager.h"

EnemyRow::EnemyRow(const Vector2 &startPosition,const string& enemyName,short enCount) : localPosition(startPosition)
{
    auto frameMap = AssetManager::getInstance()->getAnimation(enemyName);
    AnimatedSprite as(frameMap);
    auto size = as.getSize() + Vector2{2,0};

    if (enCount * as.getSize().getX() > COLS)
        return;

    for (int i = 0; i < enCount ; ++i)
    {
        auto obj = GameObject::Instantiate();
        obj->addComponent(as);
        obj->moveTo(Vector2(i * size.getX(),0));
        obj->setCollisionState(true);
        enemies.push_back(obj);
    }
}

void EnemyRow::execute(char curTick)
{
    if (enemies.empty())
    {
        parent->markedForDelete = true;
        return;
    }

    if (enemies.front()->getPosition().getX() <= 0)
        currentDirection = Vector2::Right();
    else if(enemies.back()->getPosition().getX() >= COLS - enemies.back()->getSize().getX())
        currentDirection = Vector2::Left();

    for (int i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i]->markedForDelete)
            enemies.erase(enemies.begin()+i);
        else enemies[i]->moveBy(currentDirection);
    }
}

void EnemyRow::exitCleanly()
{

}


