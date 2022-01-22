#ifndef SPACEINVADERS_RECT_H
#define SPACEINVADERS_RECT_H

#include "ScreenObject.h"

class Rect : public ScreenObject
{
private:
    short colorPair;
    void eraseInternal() override;
    void drawInternal() override;
public:
    Rect(const Vector2& position,const Vector2& size,short colorPair);
    void draw() override;
    void erase() override;
};

#endif