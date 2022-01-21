#ifndef SPACEINVADERS_SPRITERENDERER_H
#define SPACEINVADERS_SPRITERENDERER_H

#include "../CursesWrapper/Sprite.h"
#include "MovableComponent.h"

class SpriteRenderer : public MovableComponent
{
private:
    Sprite spr;
public:
    [[nodiscard]] std::string getName() const override {return "SpriteRenderer";}
    void exitCleanly() override;
    explicit SpriteRenderer(const string& spriteName);
    void draw();
    void execute(char curTick) override;
    void moveBy(const Vector2 &df) override;
    void moveTo(const Vector2 &nPos) override;
    void onAdd() override;
    [[nodiscard]] Vector2 getSize() override;
    [[nodiscard]] Vector2 getPosition() override;
    [[nodiscard]] Sprite getCurrentSprite() override;

};

#endif
