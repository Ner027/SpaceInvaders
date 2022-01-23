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
#include "../CursesWrapper/BigTextBox.h"
#include <cmath>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
    playerShip = new ShipContainer(AssetManager::getInstance()->getSpaceShips().front());
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
    using namespace std::chrono;
    auto lastFire = high_resolution_clock::now();
    long fireR = playerShip->fireRate;

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
            case ' ':
                if (duration_cast<milliseconds>(high_resolution_clock::now() - lastFire).count() >= fireR)
                {
                    shootBullet();
                    lastFire = high_resolution_clock::now();
                }
                break;
            case KEY_DOWN:
            case KEY_UP:
                player->setVelocity(0,0,1);
                break;
            default:
                break;
        }
    }
    postLevelCleanup();
}

void GameManager::startGame()
{
    mainMenu();
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
}

void GameManager::startCurrentLevel()
{
    Rect rect({0,GW_Y},{(GW_X / 2),1},8);
    rect.draw();
    Rect rect2({GW_X + 1,0},{1,GW_Y},8);
    rect2.draw();

    shouldRun = true;
    scoreBox.changeText("Score: " + to_string(score));
    scoreBox.moveTo({5,GW_Y + 2});

    livesBox.changeText("Lives: " + to_string(playerLives));
    livesBox.moveTo({GW_X - 13,GW_Y + 2});

    enemyCtl = GameObject::Instantiate();
    vector<string> enemyNames;
    switch (currentLevel)
    {
        case 0:
            enemyNames = {"enemy_basic"};
            break;
        case 1:
            enemyNames = {"enemy_medium","enemy_basic"};
            break;
        case 2:
            enemyNames = {"enemy_medium","enemy_medium","enemy_basic"};
            break;
        default:
            break;
    }
    EnemyAI enemyAi(enemyNames);
    enemyCtl->addComponent(enemyAi);
    player = GameObject::Instantiate();
    SpriteRenderer playerSkinRenderer(playerShip->spriteName);
    player->addComponent(playerSkinRenderer);
    player->moveTo(Vector2(GW_X/2,GW_Y - 2)
    - Vector2(player->getSize().getX()/2,player->getSize().getY()));

    Physics ph(player,0,0);
    player->addComponent(ph);
    player->setCollisionTester(BETTER_BOUNDING_BOX);
    createBarriers();
    gameControllerLoop();
}

void GameManager::shootBullet()
{
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
}

long GameManager::getPlayerId() const
{
    return player->getId();
}

void GameManager::gameOver()
{
    RenderManager* rm = RenderManager::getInstance();
    Sprite spr("gameover");
    spr.moveTo(centerToScreen(&spr));

    while (true)
    {
        int kp = rm->getFirstKeyPressed();
        if (kp == ' ')
            break;
    }
    spr.erase();
    mainMenu();
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
    if (currentLevel != 2)
        currentLevel++;
    GameClock::getInstance()->killAll();
    RenderManager::getInstance()->clearScreen();
    hasWon = true;
    shouldRun = false;
}

void GameManager::shipSelectionMenu()
{
    int index = 0;
    int posY;
    vector<ShipContainer> availableShips = AssetManager::getInstance()->getSpaceShips();
    RenderManager* rm = RenderManager::getInstance();
    Sprite ship(playerShip->spriteName);

    TextBox desc(getShipDescription(*playerShip),{0,0},9);

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
                delete playerShip;
                playerShip = new ShipContainer(availableShips[(index++)%availableShips.size()]);
                ship.erase();
                ship = Sprite(playerShip->spriteName);
                ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
                posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
                desc.changeText(getShipDescription(*playerShip));
                desc.moveTo({centerToScreen(&desc).getX(),posY});
                break;
            case KEY_LEFT:
                delete playerShip;
                playerShip = new ShipContainer(availableShips[(index--)%availableShips.size()]);
                ship.erase();
                ship = Sprite(playerShip->spriteName);
                ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
                posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
                desc.changeText(getShipDescription(*playerShip));
                desc.moveTo({centerToScreen(&desc).getX(),posY});
                break;
            default:
                break;
        }
    }
}

void GameManager::postLevelCleanup()
{
    shouldRun = false;
    GameClock::getInstance()->killAll();
    this_thread::sleep_for(0.5s);
    RenderManager::getInstance()->clearInputQueue();
    scoreBox.erase();
    livesBox.erase();

    string text;
    if (!hasWon)
    {
        if(--playerLives == 0)
            gameOver();
        text = to_string(playerLives)  + "\nHP\nLeft";
    }
    else
    {
        text = "You Won\nScore " + to_string(score);
        hasWon = false;
    }

    BigTextBox textBox(text, {0,0});
    textBox.moveTo(centerToScreen(&textBox));
    this_thread::sleep_for(3s);
    textBox.erase();
    startCurrentLevel();
}

string GameManager::getShipDescription(ShipContainer& sc)
{
    return sc.displayName + "\n" + "Top Speed: " + to_string(sc.velocity)
        + "\n Health Points:" + to_string(sc.healthPoints) + "\nFire Rate: "
        + to_string(round(1/((double)sc.fireRate * 0.001))) + "RPS\n" + sc.description;
}

void GameManager::mainMenu()
{
    bool keepPooling = true;
    RenderManager* rm = RenderManager::getInstance();

    int selection = 0;
    BigTextBox title("Space\nInvaders\n \nStart\n \nScoreboard\n \nExit",{170,5});

    Sprite selector("selector");
    selector.moveTo({GW_X - 15,26});

    Sprite spr("xaimite");
    spr.moveTo(Vector2(0, GW_Y/2 - spr.getSize().getY()/2));
    title.draw();

    while (keepPooling)
    {
        short kp = rm->getFirstKeyPressed();
        switch (kp)
        {
            case KEY_UP:
                if (selection == 0)
                {
                    selector.moveBy({0,24});
                    selection = 2;
                }
                else
                {
                    selector.moveBy({0,-12});
                    selection--;
                }
                break;
            case KEY_DOWN:
                if (selection == 2)
                {
                    selector.moveBy({0,-24});
                    selection = 0;
                }
                else
                {
                    selector.moveBy({0,12});
                    selection++;
                }
                break;
            case ' ':
                keepPooling = false;
                break;
            default:
                break;
        }
    }
    switch (selection)
    {
        case 0:
            rm->clearScreen();
            getName();
            rm->clearScreen();
            score = 0;
            shipSelectionMenu();
            playerLives = playerShip->healthPoints;
            startCurrentLevel();
            break;
        case 1:
            break;
        case 2:
            RenderManager::destroyInstance();
            GameClock::destroyInstance();
            AssetManager::destroyInstance();
            exit(0);
            break;
        default:
            break;
    }
}

void GameManager::getName()
{
    bool keepPooling = true;
    if (!playerName.empty())
        return;

    BigTextBox title("Please insert your name",{0,0});
    title.moveTo(centerToScreen(&title) - Vector2::Up().multiplyBy(5));

    while (keepPooling)
    {

    }
}



