#include "Rect.h"
#include "../Managers/RenderManager.h"

void Rect::eraseInternal()
{
    //Preocesso semelhante ao de desenho apenas para apagar
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
    //Iterar pelo tamanho do rectângulo e desenhar o mesmo com a cor desejada
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

Rect::Rect(const Vector2 &position, const Vector2 &size, short colorPair = 8) : ScreenObject(position,size)
{
    this->colorPair = colorPair;
}
