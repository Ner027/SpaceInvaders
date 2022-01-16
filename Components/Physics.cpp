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

    parentObject->getRenderComp()->moveBy(dl);
}


Physics::Physics(GameObject* go)
{
    this->parentObject = go;
}

void Physics::setVelocity(float _velX, float _velY)
{
    this->velX = _velX;
    this->velY = _velY;
}

Physics::Physics(GameObject *go, float x, float y)
{
    this->parentObject = go;
    this->velY = y;
    this->velX = x;
}




