#include "Managers/RenderManager.h"
#include "CursesWrapper/Sprite.h"
#include "Managers/GameClock.h"
#include "Components/Physics.h"
#include "Util/Constants.h"
#include "Components/EnemyAI.h"
#include "Managers/GameManager.h"

bool hasBul = false;

int main()
{
    this_thread::sleep_for(2s);

    RenderManager* rm = RenderManager::getInstance();
    rm->startRendering();

    GameClock* gc = GameClock::getInstance();
    gc->startGameClock();

    SpriteRenderer spr("chaimite");
    auto go = GameObject::Instantiate();
    go->addComponent(spr);

    /*
    GameManager* gm = GameManager::getInstance();
    gm->startGame();
     */
    while (true);
    return 0;
}
