#include "EnemyController.h"
#include "Enemy.h"
#include "../Util/Constants.h"
#include <queue>
#include "../Managers/AssetManager.h"
#include "Bullet.h"
#include "Physics.h"
#include "../Util/Util.h"

EnemyController::EnemyController(const Vector2 &position) : localPosition(position)
{
    for (int i = 0; i < 3; ++i)
    {
        AnimatedSprite as(enemySprName[i]);
        for (int j = 0; j < 9; ++j)
        {
            auto positionDif = as.getSize() + Vector2( 2, 2);
            positionDif*=Vector2(j,i);
            Enemy en{};
            auto obj = GameObject::Instantiate();
            obj->addComponent(en);
            obj->addComponent(as);
            obj->moveTo(localPosition + (positionDif));
            obj->setCollisionState(true);
            enemies[j + (i * 9)] = obj;
        }
    }
}

void EnemyController::execute(char curTick)
{
    if (killCount == 27)
    {
        return;
    }
    Vector2 maxPosition = Vector2::Zero();
    Vector2 minPosition = Vector2(GW_X,GW_Y);
    Vector2 outerSize = Vector2::Zero();
    queue<int> toDelete;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            auto enemy = enemies[j + (9 * i)];

            if (enemy->markedForDelete)
            {
                auto obj = GameObject::Instantiate();;
                Sprite spr(enemy->getPosition(),"empty");
                obj->addComponent(SpriteRenderer(spr));
                enemies[j + (9*i)] = obj;
                isFree[j + (i*9)] = true;
                killCount ++;
                continue;
            }

            enemy->moveBy(currentHeading);

            if (enemy->getPosition().getX() > maxPosition.getX())
            {
                maxPosition = enemy->getPosition();
                outerSize = enemy->getSize();
            }
            if (enemy->getPosition().getX() < minPosition.getX())
                minPosition = enemy->getPosition();

            if (canShoot(i,j))
            {
                if (isFree[j + i*9])
                    continue;
                int ri = randomInt(0,100);
                if (hasBullet)
                    continue;
                if (ri > 30)
                    continue;

                hasBullet = true;
                spawnBullet(enemy->getPosition() + Vector2(enemy->getSize().getX() / 2,enemy->getSize().getY() + 1));

            }
        }
    }
    int mult = killCount * 0.25 + 0.1;
    if (mult <= 0)
        mult = 1;
    if (minPosition.getX() <= 0)
        currentHeading = Vector2::Right().multiplyBy(mult);
    else if(maxPosition.getX() >= GW_X - outerSize.getX())
        currentHeading = Vector2::Left().multiplyBy(mult);

}

void EnemyController::exitCleanly()
{

}

void EnemyController::spawnBullet(const Vector2& position)
{
    GameObject* bullet = GameObject::Instantiate();
    SpriteRenderer sr2(Sprite(position,"bullet"));
    Physics pComp(nullptr,0,+30);
    bullet->addComponent(sr2);
    bullet->addComponent(pComp);
    Bullet bl(&hasBullet,bullet);
    bullet->addComponent(bl);
}

bool EnemyController::canShoot(int i,int j)
{
    if (i == 2)
        return true;

    if(i == 1 && (isFree[j + (i+ 1)*9]))
        return true;

    if(i == 0 && (isFree[j + (i+ 1)*9]) && (isFree[j + (i + 2)*9]))
        return true;

    return false;
}
