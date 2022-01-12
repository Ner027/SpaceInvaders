#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

#include "ITick.h"
#include <list>
#include "../Components/IComponent.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/AnimatedSprite.h"

class GameObject : public ITick
{
private:
    std::list<IComponent*> objectComponents;
    void tick(char curTick) override;
    GameObject();
public:
    ~GameObject();
    static GameObject* Instantiate();
    void addComponent(const SpriteRenderer& sr);
    void addComponent(const AnimatedSprite& as);

};

#endif
