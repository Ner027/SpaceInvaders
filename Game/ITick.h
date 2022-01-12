#ifndef SPACEINVADERS_ITICK_H
#define SPACEINVADERS_ITICK_H
#include <atomic>
#include <iostream>

class ITick
{
private:
    size_t selfId;
    virtual void tick(char curTick) = 0;
protected:
    explicit ITick();

    virtual ~ITick() = default;
    friend class GameClock;

public:
    std::atomic<bool> markedForDelete = false;
};

#endif
