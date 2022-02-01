#ifndef SPACEINVADERS_GAMEMANAGER_H
#define SPACEINVADERS_GAMEMANAGER_H

#include "../Game/GameObject.h"
#include "../CursesWrapper/TextBox.h"
#include "../Data/ShipContainer.h"
#include <atomic>
#include <chrono>

class GameManager
{
private:
    string playerName = "";
    short currentLevel = 0;
    short playerLives = 3;
    char currentState;
    char nextState;
    GameObject* player = nullptr;
    GameObject* enemyCtl = nullptr;
    ShipContainer* playerShip;
    atomic<int> score = 0;
    atomic<bool> shouldRun = false;
    atomic<bool> hasWon = false;
    TextBox scoreBox;
    TextBox livesBox;
    static GameManager* instance;
    void getName();
    void gameControllerLoop();
    void startCurrentLevel();
    void shootBullet();
    void gameOver();
    void postLevelCleanup();
    static void createBarriers();
    void shipSelectionMenu();
    void scoreBoardMenu();
    static void createSingleBarrier(const Vector2& position);
    void stateMachine();
    static string getShipDescription(ShipContainer& sc);
    void mainMenu();
    void winLevel();
    GameManager();
public:
    atomic<bool> enemyCanFire = true;
    static GameManager* getInstance();
    void startGame();
    void addScore(int i);
    void endCurrentLevel();
    void winCurrentLevel();
    [[nodiscard]] long getPlayerId() const;

};

#endif
