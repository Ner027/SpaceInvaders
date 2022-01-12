#ifndef SPACEINVADERS_ANIMATEDSPRITE_H
#define SPACEINVADERS_ANIMATEDSPRITE_H
#include <map>
#include "../CursesWrapper/Sprite.h"
#include "IComponent.h"

using namespace std;
class AnimatedSprite : public IComponent
{
private:
    map<char,Sprite> frames;
    char currentFrame = -1;
public:
    explicit AnimatedSprite(const map<char,Sprite>& frames);
    void execute(char curTick) override;
    void exitCleanly() override;
};

#endif
