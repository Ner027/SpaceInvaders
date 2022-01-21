#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <atomic>
#include <list>
#include "../Components/IComponent.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/AnimatedSprite.h"
#include "../Components/ICollider.h"
#include "../Components/Bullet.h"

class ICollisionTester;
class ICollider;
class Bullet;
class Physics;
class Enemy;
class EnemyAI;

using namespace std;

enum CollisionTester
{
    BETTER_BOUNDING_BOX,
};

class GameObject
{
private:
    friend class GameClock;
    long selfId = 0;
    map<string,IComponent*> objectComponents;
    MovableComponent* cachedRenderComp = nullptr;
    ICollider* colliderComponent = nullptr;
    ICollisionTester* collisionTester = nullptr;
    void insertComponent(IComponent* ic);
    void tick(char curTick);
    GameObject();
public:
    std::atomic<bool> markedForDelete = false;
    ~GameObject();
    static GameObject* Instantiate();
    void addComponent(const SpriteRenderer& sr);
    void addComponent(const Enemy& en);
    void addComponent(const AnimatedSprite& as);
    void addComponent(const Physics& ph);
    void addComponent(const Bullet& bl);
    void addComponent(const EnemyAI& en);
    void moveBy(const Vector2& df);
    void moveTo(const Vector2& nPos);
    void setCollisionTester(CollisionTester tester);
    bool isColliding(GameObject* go);
    [[nodiscard]] MovableComponent* getRenderComp();
    [[nodiscard]] Vector2 getPosition();
    [[nodiscard]] Vector2 getSize();
    [[nodiscard]] IComponent* getComponent(const string& compName);
    [[nodiscard]] long getId() const;
};

#endif
