#ifndef SPACEINVADERS_PHYSICS_H
#define SPACEINVADERS_PHYSICS_H

#include "IComponent.h"

class Physics : public IComponent
{
    void exitCleanly() override;
    void execute(char curTick) override;
};

#endif
