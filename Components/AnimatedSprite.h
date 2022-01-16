#ifndef SPACEINVADERS_ANIMATEDSPRITE_H
#define SPACEINVADERS_ANIMATEDSPRITE_H
#include <map>
#include "../CursesWrapper/Sprite.h"
#include "MovableComponent.h"

using namespace std;
class AnimatedSprite : public MovableComponent
{
private:
    map<char,Sprite> frames;
    char currentFrame = -1;
public:
    explicit AnimatedSprite(const map<char,Sprite>& frames);
    void execute(char curTick) override;
    void exitCleanly() override;
    void moveBy(const Vector2 &df) override;
    void moveTo(const Vector2 &nPos) override;
    [[nodiscard]] std::string getName() const override {return "AnimatedSprite";}
    [[nodiscard]] Vector2 getSize() override;
    [[nodiscard]] Vector2 getPosition() override;
    [[nodiscard]] Sprite getCurrentSprite() override;
};

#endif
