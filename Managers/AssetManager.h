#ifndef SPACEINVADERS_ASSETMANAGER_H
#define SPACEINVADERS_ASSETMANAGER_H
#include <map>
#include "../Data/SpriteContainer.h"
#include "../Data/ShipContainer.h"
#include <vector>

using namespace std;
class Sprite;
class AssetManager
{
private:
    //Recursos guardados em mapas para um acesso rápido
    map<string,SpriteContainer> spritePool;
    map<string,map<char,Sprite>> animPool;
    map<string,bool> gameConfigs;
    map<string,int> enemyScoreBuff;
    vector<ShipContainer> shipData;
    void tryLoadSprite(const string& spriteName,bool isAnimation);
    void tryLoadAnimation(const string& animName);
    static AssetManager* instance;
    AssetManager() = default;
    ~AssetManager();
public:
    [[nodiscard]] SpriteContainer getSprite(const string& spriteName);
    [[nodiscard]] map<char,Sprite> getAnimation(const string& animName);
    [[nodiscard]] static ifstream tryOpenFile(const string& fileName);
    [[nodiscard]] bool getConfig(const string& configName);
    [[nodiscard]] int getEnemyScore(const string& enemyName);
    [[nodiscard]] vector<ShipContainer> getSpaceShips();
    static AssetManager* getInstance();
    static void destroyInstance();
    void kill();
};


#endif
