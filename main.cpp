#include <unistd.h>
#include "Managers/RenderManager.h"
#include "CursesWrapper/Sprite.h"
#include "Managers/GameClock.h"
#include "Game/GameObject.h"
#include "Components/AnimatedSprite.h"

int main()
{
    RenderManager* rm = RenderManager::getInstance();
    rm->startRendering();

    GameClock* gc = GameClock::getInstance();
    gc->startGameClock();

    GameObject* go = GameObject::Instantiate();

    Sprite spr(Vector2(0,0),"enemy_basic");
    Sprite spr2(Vector2(0,0),"enemy_basic_2");

    map<char,Sprite> frames;
    frames.insert(pair<char,Sprite>(0,spr));
    frames.insert(pair<char,Sprite>(10,spr2));
    AnimatedSprite animSprite(frames);

    go->addComponent(animSprite);

    sleep(5);

    go->markedForDelete = true;


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true);
#pragma clang diagnostic pop

    return 0;
}
