#include "TextBox.h"
#include "../Managers/RenderManager.h"
#include "../Util/Util.h"

TextBox::TextBox(const string &str,const Vector2& pos,short colorPair = 9) : ScreenObject(pos,{(int)str.length(),1})
{
    this->colorPair = colorPair;
    lines = string_split(str,'\n');
    this->size = {largerString(),(int) lines.size()};
}

void TextBox::drawInternal()
{
    attron(COLOR_PAIR(colorPair));
    for (int i = 0;i < lines.size();++i)
    {
        string line = lines[i];
        int xOffset =( size.getX() / 2)  - (int) (line.size() / 2);
        mvprintw(localPosition.getY() + i,localPosition.getX() + xOffset,"%s",line.c_str());
    }
    attroff(COLOR_PAIR(colorPair));
}

void TextBox::eraseInternal()
{
    attron(COLOR_PAIR(1));
    for (int i = 0; i < size.getY(); ++i)
        for (int j = 0; j < size.getX(); ++j)
            mvprintw(localPosition.getY() + i,localPosition.getX() + j," ");
    attroff(COLOR_PAIR(1));
}

void TextBox::moveTo(const Vector2 &nPos)
{
    this->erase();
    this->localPosition = nPos;
    this->draw();
}

void TextBox::moveBy(const Vector2 &df)
{
    this->erase();
    this->localPosition += df;
    this->draw();
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

void TextBox::changeText(const string& newText)
{
    this->erase();
    this->lines = string_split(newText,'\n');
    this->size = {largerString(),(int) lines.size()};
    this->draw();
}

TextBox::TextBox() : ScreenObject(Vector2::Zero(),Vector2::Zero()) {}

int TextBox::largerString()
{
    int size = 0;
    for (const string& str : lines)
    {
        int s = (int) str.size();
        if (s > size)
            size = s;
    }
    return size;
}

void TextBox::addLine(const string& newLine)
{
    this->lines.push_back(newLine);
    this->size = {largerString(),(int) lines.size()};
}
