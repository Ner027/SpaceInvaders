
#include "TextBox.h"
#include "../Managers/RenderManager.h"


TextBox::TextBox(const string &str,const Vector2& pos) : ScreenObject(pos,{(int)str.length(),1})
{
    text = str;
}

void TextBox::drawInternal()
{
    attron(COLOR_PAIR(9));
    mvprintw(localPosition.getY(),localPosition.getX(),"%s", text.c_str());
    attroff(COLOR_PAIR(9));
}

void TextBox::eraseInternal()
{
    attron(COLOR_PAIR(1));
    for (int i = 0; i < size.getX(); ++i)
        mvprintw(localPosition.getY(),localPosition.getX() + i," ");
    attroff(COLOR_PAIR(1));
}

void TextBox::moveTo(const Vector2 &nPos)
{

}

void TextBox::moveBy(const Vector2 &df)
{

}

void TextBox::erase()
{
    toDraw = false;
    auto copy = new TextBox(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void TextBox::draw()
{
    toDraw = true;
    auto copy = new TextBox(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}
