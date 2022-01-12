#include "Vector2.h"

Vector2::Vector2(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2& Vector2::operator+=(const Vector2 &v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2 &r) const
{
    return {this->x + r.x, this->y + r.y};
}

int Vector2::getX() const
{
    return this->x;
}

int Vector2::getY() const
{
    return this->y;
}

bool operator==(const Vector2 &l, const Vector2 &r)
{
    return l.x == r.x && l.y == r.y;
}

