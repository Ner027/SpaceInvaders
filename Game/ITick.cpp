#include "ITick.h"
#include "../Managers/GameClock.h"

ITick::ITick()
{
    selfId = 0;
    GameClock::getInstance()->registerObject(this);
}

