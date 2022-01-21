#include "GameObject.h"
#include "../Components/Physics.h"
#include "../Managers/GameClock.h"
#include "../Components/Enemy.h"
#include "../Components/EnemyAI.h"
#include "../Components/ICollisionTester.h"
#include "../Components/BetterBoxCollider.h"


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
    GameClock::getInstance()->unregisterForCollisions(this);
    delete collisionTester;
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

void GameObject::addComponent(const Bullet& bl)
{
    if (objectComponents.contains(bl.getName()))
        return;

    auto compCopy = new Bullet(bl);
    colliderComponent = compCopy;
    objectComponents.insert(pair<string,IComponent*>(bl.getName(),compCopy));

}

bool GameObject::isColliding(GameObject *go)
{
    if (!collisionTester)
        return false;
    return collisionTester->testCollision(this,go);
}

Vector2 GameObject::getPosition()
{
    return getRenderComp()->getPosition();
}

 Vector2 GameObject::getSize()
{
    return getRenderComp()->getSize();
}


void GameObject::addComponent(const Enemy &en)
{
    if (objectComponents.contains(en.getName()))
        return;
    auto compCopy = new Enemy(en);
    objectComponents.insert(pair<string,IComponent*>(en.getName(),compCopy));

}

IComponent* GameObject::getComponent(const string& compName)
{
    for (auto& pair : objectComponents)
    {
        if (pair.second->getName() == compName)
            return pair.second;
    }
    return nullptr;
}

void GameObject::addComponent(const EnemyAI &en)
{
    if (objectComponents.contains(en.getName()))
        return;
    insertComponent(new EnemyAI(en));
}

void GameObject::insertComponent(IComponent* ic)
{
    objectComponents.insert(pair<string,IComponent*>(ic->getName(),ic));
    ic->onAdd();
}

long GameObject::getId() const
{
    return selfId;
}

void GameObject::setCollisionTester(CollisionTester tester)
{
    if (tester == BETTER_BOUNDING_BOX)
        collisionTester = new BetterBoxCollider();

    GameClock::getInstance()->registerForCollisions(this);
}


