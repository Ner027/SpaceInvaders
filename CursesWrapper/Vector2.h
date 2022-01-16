#ifndef SPACEINVADERS_VECTOR2_H
#define SPACEINVADERS_VECTOR2_H
#include <iostream>

using namespace std;
class Vector2
{
private:
    int x,y;
public:
    Vector2(const Vector2& og);
    Vector2(int x,int y);
    Vector2& operator +=(const Vector2& v);
    Vector2 operator +(const Vector2& r) const;
    Vector2 operator -(const Vector2& r) const;
    friend bool operator ==(const Vector2& l,const Vector2& r);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    static Vector2 Up();
    static Vector2 Down();
    static Vector2 Right();
    static Vector2 Left();
    static Vector2 Zero();
    const Vector2& absolute();
    [[nodiscard]] Vector2 multiplyBy(int fact) const;
    [[nodiscard]] Vector2 divideBy(int fact) const;
    friend ostream& operator << (ostream& out,const Vector2& vec);
};

#endif