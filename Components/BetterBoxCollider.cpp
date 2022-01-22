#include "BetterBoxCollider.h"

///
/// \param left Objecto que originou a colisão
/// \param right Objecto com a qual a colisão está a ser testada
/// \return Retorna o valor lógico correspondente á colisão

bool BetterBoxCollider::testCollision(GameObject *left, GameObject *right)
{
    //Se for o próprio objecto a testar a colisão consigo próprio retornar falso
    if (left->getId() == right->getId())
        return false;

    //Posições dos intervenientes na colisão
    Vector2 selfPos = left->getPosition();
    Vector2 otherPos = right->getPosition();
    //Extremos dos objectos
    Vector2 maxSelf = selfPos + left->getSize();
    Vector2 maxOther = otherPos + right->getSize();

    /*Verificação "bounding box", caso as caixas á volta dos objectos não se intercetem
     * os objectos não colidem*/

    if(selfPos.getY() > maxOther.getY())
        return false;
    if (selfPos.getX() > maxOther.getX())
        return false;
    if (maxSelf.getX() < otherPos.getX())
        return false;
    if (maxSelf.getY() < otherPos.getY())
        return false;

    //A verificação anterior é pouco precisa então é feita uma verificação adicional
    Vector2 testPos = otherPos-selfPos-Vector2::Up();
    testPos.absolute();

    //Obter a cor do "pixel" de interceção e verificar a sua cor
    auto spr = right->getRenderComp()->getCurrentSprite();
    auto pMatrix = spr.getPixelMatrix();
    auto vSize = spr.getSize().divideBy(2);
    short color = pMatrix[(testPos.getY() * (vSize.getX())) + testPos.getX()];

    //Se for a cor do background não colidem
    if (color == 1)
        return false;

    return true;
}
