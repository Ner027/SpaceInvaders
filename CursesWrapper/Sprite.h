#ifndef SPACEINVADERS_SPRITE_H
#define SPACEINVADERS_SPRITE_H

#include "ScreenObject.h"
#include <string>

class Sprite : public ScreenObject
{
private:
    friend class BigTextBox;
    Vector2 internalSize;
    std::string spriteName;
    short* pixelMatrix;
    void eraseInternal() override;
    void drawInternal() override;
public:
    explicit Sprite(const std::string& name);
    Sprite(const Sprite& og);
    Sprite();
    void draw() override;
    void erase() override;
    void moveTo(const Vector2 &nPos) override;
    void moveBy(const Vector2 &df) override;
    [[nodiscard]] const std::string& getName();
    [[nodiscard]] const short* getPixelMatrix();
};

#endif
