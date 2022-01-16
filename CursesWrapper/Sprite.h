#ifndef SPACEINVADERS_SPRITE_H
#define SPACEINVADERS_SPRITE_H

#include "ScreenObject.h"
#include <string>

class Sprite : public ScreenObject
{
private:
    Vector2 internalSize;
    std::string spriteName;
    short* pixelMatrix;
    void eraseInternal() override;
    void drawInternal() override;
public:
    Sprite(const Vector2& position,const std::string& name);
    Sprite(const Sprite& og);
    void draw() override;
    void erase() override;
    void moveTo(const Vector2 &nPos) override;
    void moveBy(const Vector2 &df) override;
    [[nodiscard]] const std::string& getName();
    [[nodiscard]] const short* getPixelMatrix();
};

#endif
