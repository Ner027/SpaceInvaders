#ifndef SPACEINVADERS_SPRITEMANAGER_H
#define SPACEINVADERS_SPRITEMANAGER_H
#include <map>
#include "../CursesWrapper/SpriteContainer.h"

using namespace std;

class SpriteManager
{
private:
    map<string,SpriteContainer> spritePool;
    void tryLoadSprite(const string& spriteName);
    static SpriteManager* instance;
public:
    [[nodiscard]] SpriteContainer getSprite(const string& spriteName);
    static SpriteManager* getInstance();
    void kill();

};

#endif
