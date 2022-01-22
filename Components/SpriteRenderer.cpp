#include "SpriteRenderer.h"
#include "../Managers/AssetManager.h"

void SpriteRenderer::execute(char curTick) {}

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

void SpriteRenderer::onAdd()
{
    this->draw();
}

SpriteRenderer::SpriteRenderer(const string &spriteName) : spr(spriteName) {}


