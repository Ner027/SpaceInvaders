#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H


#include "IComponent.h"
#include "../Game/GameObject.h"

class Enemy : public IComponent
{
public:
    bool markedForKill = false;
    Enemy();
    void exitCleanly() override;
    void execute(char curTick) override;
    [[nodiscard]] std::string getName() const override;

};


#endif
