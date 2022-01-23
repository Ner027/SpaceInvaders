#include "BigTextBox.h"
#include "../Util/Util.h"
#include "../Managers/RenderManager.h"

void BigTextBox::moveTo(const Vector2 &nPos)
{
    this->erase();
    localPosition+=nPos;
    this->relocateLines();
    this->draw();
}

void BigTextBox::moveBy(const Vector2 &df)
{
    this->erase();
    localPosition+=df;
    this->relocateLines();
    this->draw();
}

void BigTextBox::erase()
{
    toDraw = false;
    auto copy = new BigTextBox(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void BigTextBox::eraseInternal()
{
    attron(COLOR_PAIR(1));
    for (auto& line : text)
    {
        for (auto& spr : line)
        {
            spr.erase();
        }
    }
    attroff(COLOR_PAIR(1));
}

void BigTextBox::drawInternal()
{
    for (auto& line : text)
    {
        for (auto& spr : line)
        {
            spr.draw();
        }
    }
}

void BigTextBox::draw()
{
    toDraw = true;
    auto copy = new BigTextBox(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

BigTextBox::BigTextBox(const string& _text,const Vector2& position) : ScreenObject(position,{0,0})
{
    auto spl = string_split(_text,'\n');
    for (const auto& str : spl)
    {
        vector<Sprite> line;
        for (auto c : str)
        {
            string fname;
            if (c == ' ')
                fname = "Space";
            else fname = string(1,char(toupper(c)));
            line.emplace_back(fname);
        }
        text.push_back(line);
    }
    relocateLines();
}

int BigTextBox::getLargestLine()
{
    int i = 0;
    for (auto& vec : text)
    {
        int ls = getLineSize(vec);
        if (ls > i)
            i = ls;
    }
    return i;
}

void BigTextBox::relocateLines()
{
    Vector2 yDisplacement = Vector2::Zero();
    for (auto& line : text)
    {
        Vector2 displacement = localPosition + Vector2(getLargestLine(),0).divideBy(2)
                - Vector2::Right().multiplyBy(getLineSize(line)/2);
        Vector2 xDisplacement = Vector2::Zero();
        for (auto& spr : line)
        {
            auto finalPos = displacement + xDisplacement + Vector2::One() + yDisplacement;
            spr.localPosition = finalPos;
            xDisplacement += Vector2(spr.getSize().getX() + 1,0);
        }
        yDisplacement += Vector2(0,6);
    }
    this->size = {getLargestLine(),yDisplacement.getY()};
}

int BigTextBox::getLineSize(vector<Sprite>& line)
{
    int i = 0;
    for (auto& spr : line)
        i += spr.getSize().getX() + 1;
    return i;

}
