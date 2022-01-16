#include "GameObject.h"
#include "../Components/Physics.h"
#include "../Managers/GameClock.h"
#include "../CursesWrapper/TextBox.h"
#include "../Components/EnemyRow.h"
#include <sstream>
void GameObject::tick(char curTick)
{
    for (auto& pair : objectComponents)
        pair.second->execute(curTick);
}

GameObject *GameObject::Instantiate()
{
    return new GameObject();
}

GameObject::GameObject()
{
    GameClock::getInstance()->registerObject(this);
}

void GameObject::addComponent(const SpriteRenderer& sr)
{
    if (objectComponents.contains(sr.getName()))
        return;
    auto copy = new SpriteRenderer(sr);
    copy->draw();
    objectComponents.insert(pair<string,IComponent*>(sr.getName(),copy));

}

GameObject::~GameObject()
{
    for (auto& pair : objectComponents)
    {
        pair.second->exitCleanly();
        delete pair.second;
    }
}

void GameObject::addComponent(const AnimatedSprite& as)
{
    if (objectComponents.contains(as.getName()))
        return;
    auto compCopy = new AnimatedSprite(as);
    objectComponents.insert(pair<string,IComponent*>(as.getName(),compCopy));
}

void GameObject::moveBy(const Vector2 & df)
{
    getRenderComp()->moveBy(df);
}

void GameObject::moveTo(const Vector2 &nPos)
{
    getRenderComp()->moveTo(nPos);
}

MovableComponent *GameObject::getRenderComp()
{
    if (cachedRenderComp)
        return cachedRenderComp;

    IComponent* temp = nullptr;

    if (objectComponents.contains("SpriteRenderer"))
        temp = objectComponents["SpriteRenderer"];
    else if(objectComponents.contains("AnimatedSprite"))
        temp = objectComponents["AnimatedSprite"];

    if (temp)
        cachedRenderComp = dynamic_cast<MovableComponent*>(temp);
    else throw runtime_error("Componente de renderização não encontrado, impossivel mover objecto!");

    return cachedRenderComp;
}

void GameObject::addComponent(const Physics& ph)
{
    if (objectComponents.contains(ph.getName()))
        return;
    auto* compCopy = new Physics(this,ph.velX,ph.velY);
    objectComponents.insert(pair<string,IComponent*>(ph.getName(),compCopy));
}

void GameObject::setVelocity(float x,float y)
{
    if (!objectComponents.contains("Physics"))
        throw runtime_error("O objecto não tem um componente de fisicas!");

    dynamic_cast<Physics*>(objectComponents["Physics"])->setVelocity(x,y);
}

void GameObject::setCollisionState(bool b)
{
    if (b == collisionsEnabled)
        return;
    GameClock* gcInst = GameClock::getInstance();
    if (b)
        gcInst->registerForCollisions(this);
    else gcInst->unregisterForCollisions(this);
    collisionsEnabled = b;
}

void GameObject::triggerCollider(GameObject *go)
{
    if (colliderComponent)
        colliderComponent->onCollision(this,go);
}

void GameObject::addComponent(const Bullet& bl)
{
    if (objectComponents.contains(bl.getName()))
        return;

    auto compCopy = new Bullet(bl);
    compCopy->parent = this;
    colliderComponent = compCopy;
    objectComponents.insert(pair<string,IComponent*>(bl.getName(),compCopy));

}

bool GameObject::isColliding(GameObject *go)
{
    Vector2 selfPos = this->getPosition();
    Vector2 otherPos = go->getPosition();
    Vector2 maxSelf = selfPos + this->getSize();
    Vector2 maxOther = otherPos + go->getSize();

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

    auto spr = go->getRenderComp()->getCurrentSprite();
    auto pMatrix = spr.getPixelMatrix();
    auto vSize = spr.getSize().divideBy(2);
    short color = pMatrix[(testPos.getY() * (vSize.getX())) + testPos.getX()];

    if (color == 1)
        return false;

    return true;

}

Vector2 GameObject::getPosition()
{
    return getRenderComp()->getPosition();
}

 Vector2 GameObject::getSize()
{
    return getRenderComp()->getSize();
}

void GameObject::addComponent(const EnemyRow &er)
{
    if (objectComponents.contains(er.getName()))
        return;
    auto compCopy = new EnemyRow(er);
    compCopy->parent = this;
    objectComponents.insert(pair<string,IComponent*>(er.getName(),compCopy));
}


