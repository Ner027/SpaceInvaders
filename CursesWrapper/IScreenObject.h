#ifndef SPACEINVADERS_ISCREENOBJECT_H
#define SPACEINVADERS_ISCREENOBJECT_H

#include "Vector2.h"

class IScreenObject
{
protected:
    virtual void drawInternal() = 0;
    virtual void eraseInternal() = 0;
    bool toDraw = false;
    friend class RenderManager;
public:
    virtual ~IScreenObject() = default;
    virtual void draw() = 0;
    virtual void erase() = 0;
};

#endif
