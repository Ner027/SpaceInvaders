#include "GameClock.h"
#include "../Util/Constants.h"

GameClock* GameClock::instance = nullptr;

GameClock *GameClock::getInstance()
{
    if (instance == nullptr)
        instance = new GameClock();
    return instance;
}

GameClock::GameClock()
= default;

using namespace std::chrono;
[[noreturn]] void GameClock::gameLoop()
{
    while (true)
    {
        auto startTime = high_resolution_clock::now();

        if (!tickObjects.empty())
        {
            for (long i = 0;i < tickObjects.size();++i)
            {
                auto tObj = tickObjects[i];
                if (tObj->markedForDelete)
                {
                    tickObjects.erase(tickObjects.begin() + i);
                    delete tObj;
                }
                else tObj->tick(currentTick);
            }
        }

        if (currentTick != TICK_CYCLE)
            currentTick++;
        else currentTick = 0;

        while(duration_cast<microseconds>(high_resolution_clock::now() - startTime).count() <= TICK_TIME_US);

    }
}

void GameClock::startGameClock()
{
    gameThread = thread(&GameClock::gameLoop, this);
    gameThread.detach();
}

void GameClock::kill()
{
    delete instance;
}

void GameClock::registerObject(ITick* object)
{
    gameMutex.lock();

    for (ITick* obj : tickObjects)
        if (obj->selfId == object->selfId)
            return;
    tickObjects.push_back(object);
    gameMutex.unlock();
}

