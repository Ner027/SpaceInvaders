#ifndef SPACEINVADERS_SCREENOBJECT_H
#define SPACEINVADERS_SCREENOBJECT_H

#include "../Util/IncludeResolver.h"
#include "../Data/Vector2.h"

class ScreenObject
{
protected:
    Vector2 localPosition,size;
    virtual void drawInternal() = 0;
    virtual void eraseInternal() = 0;
    bool toDraw = false;
    friend class RenderManager;
public:
    ScreenObject(const Vector2& pos, const Vector2& size);
    virtual ~ScreenObject() = default;
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void moveBy(const Vector2& df);
    virtual void moveTo(const Vector2& nPos);
    const Vector2& getSize() {return size;}
    const Vector2& getPosition() {return localPosition;}
};

#endif
