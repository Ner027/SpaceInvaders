#include "SpriteRenderer.h"

void SpriteRenderer::execute(char curTick)
{

}

SpriteRenderer::SpriteRenderer(const Sprite &sprite) : spr(sprite)
{
}

void SpriteRenderer::draw()
{
    spr.draw();
}

void SpriteRenderer::exitCleanly()
{
    spr.erase();
}

void SpriteRenderer::moveBy(const Vector2 &df)
{
    spr.moveBy(df);
}

void SpriteRenderer::moveTo(const Vector2 &nPos)
{
    spr.moveTo(nPos);
}

Vector2 SpriteRenderer::getSize()
{
    return spr.getSize();
}

Vector2 SpriteRenderer::getPosition()
{
    return spr.getPosition();
}

Sprite SpriteRenderer::getCurrentSprite()
{
    return spr;
}


