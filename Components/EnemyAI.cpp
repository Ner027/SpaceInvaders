#include "EnemyAI.h"
#include "../Util/Constants.h"
#include "Enemy.h"
#include "Physics.h"
#include "../Util/Util.h"

void EnemyAI::execute(char curTick)
{
    queue<int> toRemove;
    Vector2 farRight = Vector2::Zero();
    Vector2 farLeft = Vector2::Right().multiplyBy(GW_X);

    for (auto it = enemies.cbegin();it != enemies.end();)
    {
        auto go = (*it).enemy;
        auto gridPosition = (*it).position;

        if (go->markedForDelete)
        {
            enemies.erase(it);
            isFree[gridPosition.getX() + (gridPosition.getY() * 9)];
        }
        else ++it;

        go->moveBy(currentVelocity);
        auto position = go->getPosition();
        if (position.getX() >= farRight.getX())
            farRight = position;
        if(position.getX() <= farLeft.getX())
            farLeft = position;

        if (canShoot(gridPosition))
        {
            Vector2 spawnPos(go->getPosition() + Vector2(go->getSize().getX() / 2,go->getSize().getY() + 1));
            spawnBullet(spawnPos,go);
        }

    }
    if (farRight.getX() >= GW_X - 22)
        currentVelocity = Vector2::Left();
    else if (farLeft.getX() <= 0)
        currentVelocity = Vector2::Right();
}

void EnemyAI::exitCleanly()
{
}

EnemyAI::EnemyAI(const vector<string>& enemyNames) : currentVelocity(Vector2::Right())
{
    this->enemyNames = enemyNames;
    gameManager = GameManager::getInstance();
}

void EnemyAI::onAdd()
{
    rows = (int) enemyNames.size();
    for (int i = 0; i < rows; ++i)
    {
        AnimatedSprite enemySpriteRenderer(enemyNames[i]);
        Vector2 positionDelta = Vector2(3,3) + enemySpriteRenderer.getSize();
        for (int j = 0; j < 9; ++j)
        {
            Vector2 newPosition = positionDelta * Vector2(j,i);
            auto enemy = GameObject::Instantiate();
            enemy->addComponent(enemySpriteRenderer);
            enemy->moveTo(newPosition);
            enemy->setCollisionState(true);
            Enemy en(0);
            enemies.push_back(EnemyContainer(enemy,{j,i}));
        }
    }
}

bool EnemyAI::canShoot(const Vector2& position)
{
    if (!gameManager->enemyCanFire)
        return false;

    return isFree[position.getX() + (position.getY() * 9)];
}

void EnemyAI::spawnBullet(const Vector2 &position,GameObject* parent)
{
    auto bulletObject = GameObject::Instantiate();
    SpriteRenderer spriteRenderer("bullet_enemy");
    bulletObject->addComponent(spriteRenderer);
    bulletObject->moveTo(position);
    Physics bulletPhysics(bulletObject,0,BULLET_SPEED);
    bulletObject->addComponent(bulletPhysics);
    Bullet bullet(parent);
    bulletObject->addComponent(bullet);
    gameManager->enemyCanFire = false;
}
