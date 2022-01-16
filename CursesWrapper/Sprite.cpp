#include "Sprite.h"
#include <ncurses.h>
#include <fstream>
#include <vector>
#include "../Managers/RenderManager.h"
#include "../Managers/AssetManager.h"

void Sprite::draw()
{
    toDraw = true;
    auto copy = new Sprite(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void Sprite::erase()
{
    toDraw = false;
    auto copy = new Sprite(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void Sprite::eraseInternal()
{
    attron(COLOR_PAIR(1));
    for (int i = 0; i < internalSize.getY() ; ++i)
        for (int j = 0; j < internalSize.getX(); ++j)
            mvprintw(i + localPosition.getY(),localPosition.getX() + j * 2,"  ");
    attroff(COLOR_PAIR(1));

}

void Sprite::drawInternal()
{
    for (int i = 0; i < internalSize.getY() ; ++i)
    {
        for (int j = 0; j < internalSize.getX(); ++j)
        {
            short color = pixelMatrix[(i * (internalSize.getX())) + j];
            attron(COLOR_PAIR(color));
            mvprintw(i + localPosition.getY(),localPosition.getX() + j * 2,"  ");
            attroff(COLOR_PAIR(color));
        }
    }
}

Sprite::Sprite(const Vector2 &position, const std::string& name) : ScreenObject(position,{0,0}), internalSize(0,0)
{
    this->spriteName = name;
    auto sCont = AssetManager::getInstance()->getSprite(name);
    this->pixelMatrix = sCont.getPixelMatrix();
    this->internalSize = sCont.getSize();
    this->size = {internalSize.getX() * 2,internalSize.getY()};

}


Sprite::Sprite(const Sprite& og) : ScreenObject(og.localPosition,og.size), internalSize(og.internalSize)
{
    localPosition = og.localPosition;
    toDraw = og.toDraw;
    pixelMatrix = og.pixelMatrix;
}

void Sprite::moveTo(const Vector2 &nPos)
{
    this->erase();
    this->localPosition = nPos;
    this->draw();
}

void Sprite::moveBy(const Vector2 &df)
{
    this->erase();
    this->localPosition += df;
    this->draw();
}

const std::string &Sprite::getName()
{
    return this->spriteName;
}

const short *Sprite::getPixelMatrix()
{
    return this->pixelMatrix;
}
