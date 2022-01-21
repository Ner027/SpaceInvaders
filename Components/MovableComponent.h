#ifndef SPACEINVADERS_MOVABLECOMPONENT_H
#define SPACEINVADERS_MOVABLECOMPONENT_H

#include "IComponent.h"
#include "../CursesWrapper/Vector2.h"

class MovableComponent : public IComponent
{
protected:
public:
    virtual void moveBy(const Vector2& df) = 0;
    virtual void moveTo(const Vector2& nPos) = 0;
    void execute(char curTick) override = 0;
    void exitCleanly() override = 0;
    virtual void onAdd() override = 0;
    [[nodiscard]] std::string getName() const override = 0;
    [[nodiscard]] virtual Vector2 getSize() = 0;
    [[nodiscard]] virtual Vector2 getPosition() = 0;
    [[nodiscard]] virtual Sprite getCurrentSprite() = 0;

};


#endif
