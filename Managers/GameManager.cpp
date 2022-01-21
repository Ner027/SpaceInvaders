#include <vector>
#include "GameManager.h"
#include "../Components/EnemyAI.h"
#include "../Components/Physics.h"
#include "../CursesWrapper/Rect.h"
#include "../Util/Constants.h"
#include "RenderManager.h"


GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{

}

GameManager *GameManager::getInstance()
{
    if (instance == nullptr)
        instance = new GameManager();
    return instance;
}

void GameManager::gameControllerLoop()
{
    RenderManager* rm = RenderManager::getInstance();

    while (shouldRun)
    {
        int kp = rm->getFirstKeyPressed();
        switch (kp)
        {
            case KEY_LEFT:
                player->moveBy(Vector2::Left().multiplyBy(3));
                break;
            case KEY_RIGHT:
                player->moveBy(Vector2::Right().multiplyBy(3));
                break;
            case KEY_UP:
                shootBullet();
                break;
            default:
                break;
        }
    }
}

void GameManager::startGame()
{
    startCurrentLevel();
    shouldRun = true;
    gameControllerLoop();
}

void GameManager::addScore(int i)
{
    this->score += i;
}

void GameManager::endCurrentLevel()
{
    shouldRun = false;
}

void GameManager::startCurrentLevel()
{
    Rect rect({0,GW_Y},{(GW_X / 2) + 1,1},8);
    rect.draw();
    Rect rect2({GW_X + 1,0},{1,GW_Y},8);
    rect2.draw();

    auto enemyCtl = GameObject::Instantiate();
    vector<string> enemyNames;
    switch (currentLevel)
    {
        case 0:
            enemyNames = {"enemy_basic"};
            break;
        case 1:
            enemyNames = {"enemy_basic","enemy_basic"};
            break;
        default:
            break;
    }
    EnemyAI enemyAi(enemyNames);
    enemyCtl->addComponent(enemyAi);
    player = GameObject::Instantiate();
    SpriteRenderer playerSkinRenderer(playerSkin);
    player->addComponent(playerSkinRenderer);
    Vector2 position(player->getSize().getX() / 2,-player->getSize().getY());
    position += Vector2(GW_X/2,GW_Y);
    player->moveTo(position);
}

void GameManager::shootBullet()
{
    if (!playerCanFire)
        return;
    auto bulletObject = GameObject::Instantiate();
    SpriteRenderer spriteRenderer("bullet");
    bulletObject->addComponent(spriteRenderer);

    bulletObject->moveTo({player->getPosition().getX() + (player->getSize().getX() / 2) - 1
                          ,player->getPosition().getY() - 2});
    Bullet bullet(player);
    Physics bulletPhysics(bulletObject,0,-BULLET_SPEED);
    bulletObject->addComponent(bullet);
    bulletObject->addComponent(bulletPhysics);
    playerCanFire = false;
}

long GameManager::getPlayerId() const
{
    return player->getId();
}

