#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H


#include "IComponent.h"
#include "../Game/GameObject.h"
#include <vector>

class Enemy : public IComponent
{
private:
    int score = 0;
public:
    Enemy(int score);
    void exitCleanly() override;
    void execute(char curTick) override;
    void onAdd() override;
    [[nodiscard]] std::string getName() const override {return "Enemy";}

};


#endif
