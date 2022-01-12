#include "Sprite.h"
#include <ncurses.h>
#include <fstream>
#include <vector>
#include "../Managers/RenderManager.h"
#include "../Managers/SpriteManager.h"

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
    for (int i = 0; i < size.getY() ; ++i)
        for (int j = 0; j < size.getX(); ++j)
            mvprintw(i + localPosition.getY(),localPosition.getX() + j * 2,"  ");
    attroff(COLOR_PAIR(1));

}

void Sprite::drawInternal()
{
    for (int i = 0; i < size.getY() ; ++i)
    {
        for (int j = 0; j < size.getX(); ++j)
        {
            short color = pixelMatrix[(i * (size.getX())) + j];
            attron(COLOR_PAIR(color));
            mvprintw(i + localPosition.getY(),localPosition.getX() + j * 2,"  ");
            attroff(COLOR_PAIR(color));
        }
    }
}

Sprite::Sprite(const Vector2 &position, const std::string& name) : size(0,0), localPosition(position)
{
    this->spriteName = name;
    auto sCont = SpriteManager::getInstance()->getSprite(name);
    this->pixelMatrix = sCont.getPixelMatrix();
    this->size = sCont.getSize();
}


Sprite::Sprite(const Sprite& og) : localPosition(og.localPosition), size(og.size)
{
    toDraw = og.toDraw;
    pixelMatrix = og.pixelMatrix;
}
