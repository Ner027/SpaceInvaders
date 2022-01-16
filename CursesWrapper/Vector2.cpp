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

Vector2 Vector2::Up()
{
    return {0,-1};
}

Vector2 Vector2::Down()
{
    return {0, 1};
}

Vector2 Vector2::Right()
{
    return {1, 0};
}

Vector2 Vector2::Left()
{
    return {-1, 0};
}

Vector2 Vector2::Zero()
{
    return {0, 0};
}

Vector2::Vector2(const Vector2& og)
{
    this->x = og.x;
    this->y = og.y;
}

Vector2 Vector2::operator-(const Vector2 &r) const
{
    return {this->x - r.x, this->y - r.y};
}


ostream &operator<<(ostream &out, const Vector2 &vec)
{
    out << "X:" << vec.x << ",Y:" << vec.y;
    return out;
}

const Vector2 &Vector2::absolute()
{
    this->y = abs(y);
    this->x = abs(x);
    return *this;
}

Vector2 Vector2::multiplyBy(int factor) const
{
    return {x*factor,y*factor};
}

Vector2 Vector2::divideBy(int factor) const
{
    return {x/factor,y/factor};
}





