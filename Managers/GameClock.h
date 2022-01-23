#ifndef SPACEINVADERS_GAMECLOCK_H
#define SPACEINVADERS_GAMECLOCK_H

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include "../Game/GameObject.h"

using namespace std;
class GameClock
{
private:
    mutex gameMutex;
    thread gameThread;
    atomic<char> currentTick = 0;
    atomic<bool> keepRunning = false;
    long currentIdentifier = 0;
    vector<GameObject*> tickObjects;
    vector<GameObject*> registeredCollisionObjects;
    static GameClock* instance;
    void gameLoop();
    GameClock() = default;
    ~GameClock();
public:
    [[nodiscard]] static GameClock* getInstance();
    void registerObject(GameObject* object);
    void registerForCollisions(GameObject* obj);
    void unregisterForCollisions(GameObject* obj);
    void startGameClock();
    void killAll();
    static void destroyInstance();
};




#endif
