#ifndef SPACEINVADERS_ASSETMANAGER_H
#define SPACEINVADERS_ASSETMANAGER_H
#include <map>
#include "../CursesWrapper/SpriteContainer.h"
#include "../Game/Level.h"

using namespace std;
class Sprite;
class AssetManager
{
private:
    map<string,SpriteContainer> spritePool;
    map<string,map<char,Sprite>> animPool;
    map<string,bool> gameConfigs;
    void tryLoadSprite(const string& spriteName,bool isAnimation);
    void tryLoadAnimation(const string& animName);
    static AssetManager* instance;
public:
    [[nodiscard]] SpriteContainer getSprite(const string& spriteName);
    [[nodiscard]] map<char,Sprite> getAnimation(const string& animName);
    [[nodiscard]] static ifstream tryOpenFile(const string& fileName);
    [[nodiscard]] bool getConfig(const string& configName);
    static AssetManager* getInstance();
    void kill();
};


#endif
