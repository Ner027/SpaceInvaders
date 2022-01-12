#ifndef SPACEINVADERS_ICOMPONENT_H
#define SPACEINVADERS_ICOMPONENT_H

class IComponent
{
public:
    virtual void execute(char curTick) = 0;
    virtual void exitCleanly() = 0;
    virtual ~IComponent() = default;
};

#endif
