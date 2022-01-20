#include "Managers/RenderManager.h"
#include "CursesWrapper/Sprite.h"
#include "Managers/GameClock.h"
#include "Components/EnemyController.h"
#include "Components/Physics.h"
#include "Util/Constants.h"

bool hasBul = false;

int main()
{
    this_thread::sleep_for(2s);
    RenderManager* rm = RenderManager::getInstance();
    rm->startRendering();

    GameClock* gc = GameClock::getInstance();
    gc->startGameClock();

    GameObject* enemyRow = GameObject::Instantiate();

    EnemyController ec(Vector2::Zero());
    enemyRow->addComponent(ec);

    GameObject* player = GameObject::Instantiate();
    auto pPos = Vector2(GW_X/2,GW_Y);
    SpriteRenderer sr(Sprite(pPos,"ship_basic"));
    player->addComponent(sr);
    player->moveBy(Vector2::Up().multiplyBy(player->getSize().getY()));
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
                player->moveBy(Vector2::Left().multiplyBy(4));
                break;
            case KEY_RIGHT:
                player->moveBy(Vector2::Right().multiplyBy(4));
                break;
            case KEY_UP:
                if (hasBul)
                    break;
                Vector2 spawnPos = player->getPosition() + Vector2(player->getSize().getX()/2 - 1,-2);
                GameObject* bullet = GameObject::Instantiate();
                SpriteRenderer sr2(Sprite(spawnPos,"bullet"));
                Physics ph2(nullptr,0,-30);
                bullet->addComponent(sr2);
                bullet->addComponent(ph2);
                Bullet bl(&hasBul,bullet);
                bullet->addComponent(bl);
                hasBul = true;
                break;

        }

    }
#pragma clang diagnostic pop

    return 0;
}
