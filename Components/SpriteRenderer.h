#ifndef SPACEINVADERS_SPRITERENDERER_H
#define SPACEINVADERS_SPRITERENDERER_H

#include "IComponent.h"
#include "../CursesWrapper/Sprite.h"

class SpriteRenderer : public IComponent
{
private:
    Sprite spr;
public:
    void exitCleanly() override;
    explicit SpriteRenderer(const Sprite& sprite);
    void draw();
    void execute(char curTick) override;
};

#endif
