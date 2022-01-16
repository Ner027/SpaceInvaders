#ifndef SPACEINVADERS_ICOMPONENT_H
#define SPACEINVADERS_ICOMPONENT_H
#include <string>

class IComponent
{
public:
    [[nodiscard]] virtual std::string getName() const = 0;
    virtual void execute(char curTick) = 0;
    virtual void exitCleanly() = 0;
    virtual ~IComponent() = default;
};

#endif
