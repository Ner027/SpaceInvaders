#ifndef SPACEINVADERS_VECTOR2_H
#define SPACEINVADERS_VECTOR2_H

class Vector2
{
private:
    int x,y;
public:
    Vector2(int x,int y);
    Vector2& operator +=(const Vector2& v);
    Vector2 operator +(const Vector2& r) const;
    friend bool operator ==(const Vector2& l,const Vector2& r);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
};

#endif