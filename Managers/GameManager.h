#ifndef SPACEINVADERS_GAMEMANAGER_H
#define SPACEINVADERS_GAMEMANAGER_H

#include "../Game/GameObject.h"
#include <atomic>

class GameManager
{
private:
    short currentLevel = 0;
    short playerLives;
    string playerSkin = "ship_basic";
    GameObject* player;
    atomic<int> score = 0;
    bool shouldRun = false;
    static GameManager* instance;
    void gameControllerLoop();
    void startCurrentLevel();
    void shootBullet();
    GameManager();
public:
    atomic<bool> playerCanFire = true;
    atomic<bool> enemyCanFire = true;
    static GameManager* getInstance();
    void startGame();
    void addScore(int i);
    void endCurrentLevel();
    [[nodiscard]] long getPlayerId() const;

};

#endif
