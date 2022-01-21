#ifndef SPACEINVADERS_GAMEMANAGER_H
#define SPACEINVADERS_GAMEMANAGER_H

#include "../Game/GameObject.h"
#include "../CursesWrapper/TextBox.h"
#include <atomic>

class GameManager
{
private:
    short currentLevel = 0;
    short playerLives = 3;
    string playerSkin = "ship_basic";
    GameObject* player;
    GameObject* enemyCtl;
    atomic<int> score = 0;
    atomic<bool> shouldRun = false;
    TextBox scoreBox;
    TextBox livesBox;
    static GameManager* instance;
    void gameControllerLoop();
    void startCurrentLevel();
    void shootBullet();
    void gameOver();
    void restartLevel();
    void backToMenu();
    void createBarriers();
    void createSingleBarrier(const Vector2& position);
    GameManager();
public:
    atomic<bool> playerCanFire = true;
    atomic<bool> enemyCanFire = true;
    static GameManager* getInstance();
    void startGame();
    void addScore(int i);
    void endCurrentLevel();
    void winCurrentLevel();
    void removeLife();
    [[nodiscard]] long getPlayerId() const;

};

#endif
