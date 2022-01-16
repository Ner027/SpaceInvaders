#include "Rect.h"
#include "../Managers/RenderManager.h"

void Rect::eraseInternal()
{
    attron(COLOR_PAIR(1));
    for (int i = 0; i < size.getY(); ++i)
    {
        for (int j = 0; j < size.getX(); ++j)
        {
            mvprintw(i + localPosition.getY(),j + localPosition.getX(),"  ");
        }
    }
    attroff(COLOR_PAIR(1));
}

void Rect::drawInternal()
{
    attron(COLOR_PAIR(colorPair));
    for (int i = 0; i < size.getY(); ++i)
    {
        for (int j = 0; j < size.getX() * 2; j+=2)
        {
            mvprintw(i + localPosition.getY(),j + localPosition.getX(),"  ");
        }
    }
    attroff(COLOR_PAIR(colorPair));
}

void Rect::draw()
{
    toDraw = true;
    auto copy = new Rect(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void Rect::erase()
{
    toDraw = false;
    auto copy = new Rect(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);

}

void Rect::moveBy(const Vector2 &df)
{

}

void Rect::moveTo(const Vector2 &nPos)
{

}

Rect::Rect(const Vector2 &position, const Vector2 &size, short colorPair = 8) : ScreenObject(position,size)
{
    this->colorPair = colorPair;
}
