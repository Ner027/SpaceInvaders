#include "Vector2.h"

Vector2::Vector2(int x, int y)
{
    this->x = x;
    this->y = y;
}

///
/// \param Vector para somar com
/// \return Vector ao qual foi adicionado
Vector2& Vector2::operator+=(const Vector2 &v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

///
/// \param Vector para somar com
/// \return Novo vector com valores correspondete a soma dos dois
Vector2 Vector2::operator+(const Vector2 &r) const
{
    return {this->x + r.x, this->y + r.y};
}

///
/// \return Componente X do vector
int Vector2::getX() const
{
    return this->x;
}

///
/// \return Componente Y do vector
int Vector2::getY() const
{
    return this->y;
}

/// 
/// \param l Operando da esquerda
/// \param r Operando da direta
/// \return Valor lógico da comparação entre ambos os vectes
bool operator==(const Vector2 &l, const Vector2 &r)
{
    return l.x == r.x && l.y == r.y;
}

/// 
/// \return Vector 0 -1
Vector2 Vector2::Up()
{
    return {0,-1};
}

/// 
/// \return Vector 0 1
Vector2 Vector2::Down()
{
    return {0, 1};
}

/// 
/// \return Vector 1 0
Vector2 Vector2::Right()
{
    return {1, 0};
}

///
/// \return Vector -1 0
Vector2 Vector2::Left()
{
    return {-1, 0};
}

///
/// \return Vector 0 0
Vector2 Vector2::Zero()
{
    return {0, 0};
}

///
/// \param r  Vector a subtrair
/// \return Novo vector com valores correspondetes á subtração entre 2 vectores
Vector2 Vector2::operator-(const Vector2 &r) const
{
    return {this->x - r.x, this->y - r.y};
}

///
/// \param out Output stream
/// \param vec Vector a imprimir
/// \return Output stream
ostream &operator<<(ostream &out, const Vector2 &vec)
{
    out << "X:" << vec.x << ",Y:" << vec.y;
    return out;
}

/// Coloca ambos os valores do vetor em valor absoluto
/// \return Próprio vector já alterado
const Vector2 &Vector2::absolute()
{
    this->y = abs(y);
    this->x = abs(x);
    return *this;
}

///
/// \param factor Fator multiplicador
/// \return Vector com todas as componentes multiplicadas por factor
Vector2 Vector2::multiplyBy(int factor) const
{
    return {x*factor,y*factor};
}

///
/// \param factor Fator divisor
/// \return Vector com todas as componentes divididas por factor
Vector2 Vector2::divideBy(int factor) const
{
    return {x/factor,y/factor};
}


///
/// \param r  Vector a somar
/// \return Novo vector com valores correspondetes á soma entre 2 vectores
Vector2 Vector2::operator*(const Vector2 &r) const
{
    return {this->x * r.x,this->y * r.y};
}

///
/// \param r Vector a multiplicar
/// \return Próprio vector com cada componente multiplicada pela componente correspondente de outro vector
Vector2 &Vector2::operator*=(const Vector2 &r)
{
    this->y *= r.y;
    this->x *= r.x;
    return *this;
}

Vector2 Vector2::One()
{
    return {1,1};
}






