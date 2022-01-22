#include <cmath>
#include "Physics.h"
#include "../Util/Constants.h"

void Physics::exitCleanly()
{

}

void Physics::execute(char curTick)
{

    float deltaTime = 0.05;
    int x = (int) round(deltaTime * velX);
    int y = (int) round(deltaTime * velY);
    Vector2 dl = {x,y};
    parentObject->getRenderComp()->moveBy(dl.multiplyBy(multiplier));
    Vector2 pos = parentObject->getPosition();
    Vector2 upperBound = parentObject->getSize() + parentObject->getPosition();
    if(pos.getX() < 2 || upperBound.getX() >= GW_X || pos.getY() < 0 || upperBound.getY() >= GW_Y - 1)
    {
        if (gameManager->getPlayerId() == parentObject->getId())
        {
            parentObject->setVelocity(0,0,1);
            return;
        }
        parentObject->markedForDelete = true;
    }
}

void Physics::setVelocity(float _velX, float _velY,int _multiplier = 1)
{
    this->multiplier = _multiplier;
    this->velX = _velX;
    this->velY = _velY;
}

void Physics::onAdd()
{

}

Physics::Physics(GameObject *go, float x, float y, int _multiplier)
{
    this->multiplier = _multiplier;
    this->parentObject = go;
    this->velY = y;
    this->velX = x;
}




