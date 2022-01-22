#include <vector>
#include "GameManager.h"
#include "../Components/EnemyAI.h"
#include "../Components/Physics.h"
#include "../CursesWrapper/Rect.h"
#include "../Util/Constants.h"
#include "GameClock.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "../Util/Util.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
    playerShip = new ShipContainer(AssetManager::getInstance()->getSpaceShips().front());
    Rect rect({0,GW_Y},{(GW_X / 2),1},8);
    rect.draw();
    Rect rect2({GW_X + 1,0},{1,GW_Y},8);
    rect2.draw();
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
                player->setVelocity(-playerShip->velocity,0,2);
                break;
            case KEY_RIGHT:
                player->setVelocity(playerShip->velocity,0,2);
                break;
            case KEY_UP:
                shootBullet();
                break;
            default:
                break;
        }
    }
    enemyCtl->markedForDelete = true;
    this_thread::sleep_for(2s);
    removeLife();
}

void GameManager::startGame()
{
    shipSelectionMenu();
    startCurrentLevel();
    shouldRun = true;
    gameControllerLoop();
}

void GameManager::addScore(int i)
{
    if (!shouldRun)
        return;
    this->score += i;
    scoreBox.changeText("Score: " + to_string(score));
}

void GameManager::endCurrentLevel()
{
    shouldRun = false;
    GameClock::getInstance()->killAll();
}

void GameManager::startCurrentLevel()
{

    scoreBox.changeText("Score: 0");
    scoreBox.moveTo({5,GW_Y + 2});

    livesBox.changeText("Lives: " + to_string(playerLives));
    livesBox.moveTo({GW_X - 13,GW_Y + 2});

    enemyCtl = GameObject::Instantiate();
    vector<string> enemyNames;
    currentLevel = 2;
    switch (currentLevel)
    {
        case 0:
            enemyNames = {"enemy_basic"};
            break;
        case 1:
            enemyNames = {"enemy_basic","enemy_medium"};
            break;
        case 2:
            enemyNames = {"enemy_basic","enemy_medium","enemy_medium"};
            break;
        default:
            break;
    }
    EnemyAI enemyAi(enemyNames);
    enemyCtl->addComponent(enemyAi);
    player = GameObject::Instantiate();
    SpriteRenderer playerSkinRenderer(playerShip->spriteName);
    player->addComponent(playerSkinRenderer);
    Vector2 position(player->getSize().getX() / 2,-player->getSize().getY());
    position += Vector2(GW_X/2,GW_Y - 2);
    player->moveTo(position);
    Physics ph(player,0,0);
    player->addComponent(ph);
    player->setCollisionTester(BETTER_BOUNDING_BOX);
    createBarriers();

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
    bulletObject->setCollisionTester(BETTER_BOUNDING_BOX);
    playerCanFire = false;
}

long GameManager::getPlayerId() const
{
    return player->getId();
}

void GameManager::removeLife()
{
    playerLives--;
    if (playerLives == 0)
        gameOver();

    livesBox.changeText("Lives: " + to_string(playerLives));
    startGame();
}

void GameManager::gameOver()
{
    RenderManager* rm = RenderManager::getInstance();
    Sprite spr("gameover");
    spr.moveTo({(GW_X / 2) - spr.getSize().getX() / 2,(GW_Y / 2) - spr.getSize().getY() / 2});

    bool waitInput = true;
    while (waitInput)
    {
        int kp = rm->getFirstKeyPressed();
        switch (kp)
        {
            case KEY_DOWN:
                waitInput = false;
                restartLevel();
                break;
            case 27:
                waitInput = false;
                backToMenu();
                break;
            default:
                break;
        }
    }
}

void GameManager::restartLevel()
{
    this->playerLives = 3;
    this->score = 0;
    startGame();
}

void GameManager::backToMenu()
{

}

void GameManager::createBarriers()
{
    createSingleBarrier({11,GW_Y - 25});
    createSingleBarrier({GW_X - 52,GW_Y - 25});
    createSingleBarrier({(GW_X/2) - 20,GW_Y  - 25});
}

void GameManager::createSingleBarrier(const Vector2& position)
{
    SpriteRenderer sprite("block");
    for (int i = position.getY(); i < position.getY() + 5; ++i)
    {
        for (int j = position.getX(); j < position.getX() + 40; j+=2)
        {
            auto go = GameObject::Instantiate();
            go->addComponent(sprite);
            go->setCollisionTester(BETTER_BOUNDING_BOX);
            go->moveTo({j,i});
        }
    }
}

void GameManager::winCurrentLevel()
{
    GameClock::getInstance()->killAll();
    RenderManager::getInstance()->clearScreen();
    shouldRun = false;
}

void GameManager::shipSelectionMenu()
{
    int index = 0;
    int posY;
    vector<ShipContainer> availableShips = AssetManager::getInstance()->getSpaceShips();
    RenderManager* rm = RenderManager::getInstance();
    Sprite ship(playerShip->spriteName);

    TextBox desc(playerShip->displayName + "\n" + playerShip->description +
    "\nTop Speed: " + to_string(playerShip->velocity),{0,0},9);

    ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
    posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
    desc.moveTo({centerToScreen(&desc).getX(),posY});

    while(true)
    {
        short kp = rm->getFirstKeyPressed();

        switch (kp)
        {
            case ' ':
                ship.erase();
                desc.erase();
                return;
            case KEY_RIGHT:
                playerShip = new ShipContainer(availableShips[(index++)%availableShips.size()]);
                ship.erase();
                ship = Sprite(playerShip->spriteName);
                ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
                posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
                desc.erase();
                desc.changeText(playerShip->displayName + "\n" + playerShip->description
                + "\nTop Speed: " + to_string(playerShip->velocity));
                desc.moveTo({centerToScreen(&desc).getX(),posY});
                break;
            default:
                break;
        }
    }
}


