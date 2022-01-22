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
                if (tObj->colliderComponent)
                {
                    for (auto c : registeredCollisionObjects)
                    {
                        if (c->isColliding(tObj) && c->selfId != tObj->selfId)
                            tObj->colliderComponent->onCollision(tObj,c);

                    }
                }
                if (tObj->markedForDelete)
                {
                    unregisterForCollisions(tObj);
                    tickObjects.erase(tickObjects.begin() + i);
                    delete tObj;
                }
                else tObj->tick(currentTick);
            }
        }

        if (currentTick != TICK_CYCLE + 1)
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

void GameClock::registerObject(GameObject* object)
{
    gameMutex.lock();
    object->selfId = currentIdentifier++;
    tickObjects.push_back(object);
    gameMutex.unlock();
}

void GameClock::registerForCollisions(GameObject* tObj)
{
    gameMutex.lock();
    for (auto o : registeredCollisionObjects)
        if (o->selfId == tObj->selfId)
            return;
    registeredCollisionObjects.push_back(tObj);
    gameMutex.unlock();
}

void GameClock::unregisterForCollisions(GameObject *obj)
{
    for (int i = 0; i < registeredCollisionObjects.size(); ++i)
    {
        if (obj->selfId == registeredCollisionObjects[i]->selfId)
        {
            registeredCollisionObjects.erase(registeredCollisionObjects.cbegin() + i);
            return;
        }
    }
}

void GameClock::killAll()
{
    for (auto go : tickObjects)
        go->markedForDelete = true;
}
