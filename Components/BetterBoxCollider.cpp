#include "BetterBoxCollider.h"

bool BetterBoxCollider::testCollision(GameObject *left, GameObject *right)
{
    if (left->getId() == right->getId())
        return false;

    Vector2 selfPos = left->getPosition();
    Vector2 otherPos = right->getPosition();
    Vector2 maxSelf = selfPos + left->getSize();
    Vector2 maxOther = otherPos + right->getSize();

    if(selfPos.getY() > maxOther.getY())
        return false;
    if (selfPos.getX() > maxOther.getX())
        return false;
    if (maxSelf.getX() < otherPos.getX())
        return false;
    if (maxSelf.getY() < otherPos.getY())
        return false;


    Vector2 testPos = otherPos-selfPos-Vector2::Up();
    testPos.absolute();

    auto spr = right->getRenderComp()->getCurrentSprite();
    auto pMatrix = spr.getPixelMatrix();
    auto vSize = spr.getSize().divideBy(2);
    short color = pMatrix[(testPos.getY() * (vSize.getX())) + testPos.getX()];

    if (color == 1)
        return false;

    return true;
}
