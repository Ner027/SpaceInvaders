#include "SpriteContainer.h"

SpriteContainer::SpriteContainer(short *pixelMatrix,const Vector2& size): size(size)
{
    this->pixelMatrix = pixelMatrix;
}

short *SpriteContainer::getPixelMatrix()
{
    return this->pixelMatrix;
}

Vector2 SpriteContainer::getSize() const
{
    return this->size;
}
