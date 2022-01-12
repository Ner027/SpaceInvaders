#include "SpriteRenderer.h"

void SpriteRenderer::execute(char curTick)
{
    if (curTick == 0)
        spr.erase();
    else if (curTick == 10)
        spr.draw();
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

