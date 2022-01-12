#ifndef SPACEINVADERS_SPRITE_H
#define SPACEINVADERS_SPRITE_H

#include "IScreenObject.h"
#include <string>

class Sprite : public IScreenObject
{
private:
    Vector2 size,localPosition;
    std::string spriteName;
    short* pixelMatrix;
    void eraseInternal() override;
    void drawInternal() override;
public:
    Sprite(const Vector2& position,const std::string& name);
    Sprite(const Sprite& og);
    void draw() override;
    void erase() override;
};

#endif
