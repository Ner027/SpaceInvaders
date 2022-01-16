#include "Managers/RenderManager.h"
#include "CursesWrapper/Sprite.h"
#include "Managers/GameClock.h"
#include "Components/EnemyRow.h"
#include "Components/Physics.h"
int main()
{
    RenderManager* rm = RenderManager::getInstance();
    rm->startRendering();

    GameClock* gc = GameClock::getInstance();
    gc->startGameClock();

    GameObject* enemyRow = GameObject::Instantiate();
    EnemyRow er(Vector2::Zero(),"enemy_basic",5);
    enemyRow->addComponent(er);

    GameObject* player = GameObject::Instantiate();

    auto pPos = Vector2(COLS/2,30);
    SpriteRenderer sr(Sprite(pPos,"ship_basic"));
    player->addComponent(sr);
    Physics ph{nullptr,0,0};
    player->addComponent(ph);



#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true)
    {
        short key = rm->getFirstKeyPressed();
        switch (key)
        {
            case KEY_LEFT:
                player->moveBy(Vector2::Left().multiplyBy(2));
                break;
            case KEY_RIGHT:
                player->moveBy(Vector2::Right().multiplyBy(2));
                break;
            case KEY_UP:
                Vector2 spawnPos = player->getPosition() + Vector2(player->getSize().getX()/2 - 1,-2);
                GameObject* bullet = GameObject::Instantiate();
                SpriteRenderer sr2(Sprite(spawnPos,"bullet"));
                Physics ph2(nullptr,0,-10);
                bullet->addComponent(sr2);
                bullet->addComponent(ph2);
                Bullet bl;
                bullet->addComponent(bl);
                break;

        }

    }
#pragma clang diagnostic pop

    return 0;
}
