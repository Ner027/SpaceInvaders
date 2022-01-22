#ifndef SPACEINVADERS_SPRITECONTAINER_H
#define SPACEINVADERS_SPRITECONTAINER_H

#include "Vector2.h"

class SpriteContainer
{
private:
    short* pixelMatrix = nullptr;
    Vector2 size;
public:
    SpriteContainer(short* pixelMatrix,const Vector2& size);
    SpriteContainer() : size(0,0){};
    [[nodiscard]] short* getPixelMatrix();
    [[nodiscard]] Vector2 getSize() const;
};

#endif
