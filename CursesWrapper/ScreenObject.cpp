#include "ScreenObject.h"

ScreenObject::ScreenObject(const Vector2& pos, const Vector2& size) : localPosition(pos), size(size){}

void ScreenObject::moveBy(const Vector2 &df)
{
    this->erase();
    this->localPosition += df;
    this->draw();
}

void ScreenObject::moveTo(const Vector2 &nPos)
{
    this->erase();
    this->localPosition = nPos;
    this->draw();
}

