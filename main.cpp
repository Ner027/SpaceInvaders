#include "Managers/RenderManager.h"
#include "CursesWrapper/Sprite.h"
#include "Managers/GameClock.h"
#include "Components/Physics.h"
#include "Components/EnemyAI.h"
#include "CursesWrapper/BigTextBox.h"

int main()
{
    RenderManager* rm = RenderManager::getInstance();
    rm->startRendering();

    GameClock* gc = GameClock::getInstance();
    gc->startGameClock();

    GameManager* gm = GameManager::getInstance();
    gm->startGame();

    while (true);
    return 0;
}
