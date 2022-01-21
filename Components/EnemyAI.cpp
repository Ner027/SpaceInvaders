#include "EnemyAI.h"
#include "../Util/Constants.h"
#include "Enemy.h"
#include "Physics.h"
#include "../Util/Util.h"
#include "../Managers/AssetManager.h"

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
            isFree[gridPosition.getX() + (gridPosition.getY() * 9)] = true;
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
            lastEnemy = gridPosition;
        }

    }
    if (farRight.getX() >= GW_X - 22)
        currentVelocity = Vector2::Left();
    else if (farLeft.getX() <= 0)
        currentVelocity = Vector2::Right();
}

void EnemyAI::exitCleanly()
{
    for (auto& go : enemies)
        go.enemy->markedForDelete = true;
}

EnemyAI::EnemyAI(const vector<string>& enemyNames) : currentVelocity(Vector2::Right())
{
    this->enemyNames = enemyNames;
    gameManager = GameManager::getInstance();
}

void EnemyAI::onAdd()
{
    AssetManager* am = AssetManager::getInstance();
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
            Enemy en(am->getEnemyScore(enemyNames[i]));
            enemy->addComponent(en);
            enemy->setCollisionTester(BETTER_BOUNDING_BOX);
            enemies.push_back(EnemyContainer(enemy,{j,i}));
        }
    }
}

bool EnemyAI::canShoot(const Vector2& position)
{
    if (!gameManager->enemyCanFire)
        return false;

    if (position == lastEnemy)
        return false;

    int ri = randomInt(0,100);
    if (ri > 0)
        return false;

    for (int i = position.getY() + 1; i < rows; ++i)
    {
        if (!isFree[position.getX() + (i * 9) ])
            return false;
    }

    return true;

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
    bulletObject->setCollisionTester(BETTER_BOUNDING_BOX);
    gameManager->enemyCanFire = false;
}
