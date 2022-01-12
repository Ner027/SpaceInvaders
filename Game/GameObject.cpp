#include "GameObject.h"

void GameObject::tick(char curTick)
{
    for (auto comp : objectComponents)
        comp->execute(curTick);
}

GameObject *GameObject::Instantiate()
{
    return new GameObject();
}

GameObject::GameObject() : ITick()
{

}

void GameObject::addComponent(const SpriteRenderer& sr)
{
    auto compCopy = new SpriteRenderer(sr);
    compCopy->draw();
    objectComponents.push_front(compCopy);
}

GameObject::~GameObject()
{
    for (auto ic : objectComponents)
    {
        ic->exitCleanly();
        delete ic;
    }
}

void GameObject::addComponent(const AnimatedSprite& as)
{
    auto compCopy = new AnimatedSprite(as);
    objectComponents.push_front(compCopy);
}

