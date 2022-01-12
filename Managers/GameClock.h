#ifndef SPACEINVADERS_GAMECLOCK_H
#define SPACEINVADERS_GAMECLOCK_H
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include "../Game/ITick.h"

using namespace std;
class GameClock
{
private:
    mutex gameMutex;
    thread gameThread;
    atomic<char> currentTick = 0;
    atomic<size_t> currentIdentifier = 0;
    vector<ITick*> tickObjects;
    static GameClock* instance;
    [[noreturn]] void gameLoop();
    GameClock();
public:
    atomic<short> pressedKey{};
    [[nodiscard]] static GameClock* getInstance();
    static void kill();
    void registerObject(ITick* object);
    void startGameClock();

};




#endif
