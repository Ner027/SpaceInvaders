#ifndef SPACEINVADERS_PHYSICS_H
#define SPACEINVADERS_PHYSICS_H

#include "IComponent.h"
#include "../CursesWrapper/Vector2.h"
#include "../Game/GameObject.h"

class Physics : public IComponent
{
private:
    float velX{},velY{};
    GameObject* parentObject;
    friend class GameObject;
    int multiplier;
    GameManager* gameManager = GameManager::getInstance();
public:
    Physics(GameObject* go,float x,float y,int _multiplier = 1);
    void exitCleanly() override;
    void execute(char curTick) override;
    void onAdd() override;
    [[nodiscard]] std::string getName() const override{return "Physics";}
    void setVelocity(float velX,float velY,int _multiplier);
};


#endif
