#include "AssetManager.h"
#include "../Util/Constants.h"
#include "../Util/Util.h"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "../CursesWrapper/Sprite.h"
#include <iostream>
AssetManager* AssetManager::instance = nullptr;

void AssetManager::tryLoadSprite(const string& spriteName,bool isAnimation)
{
    stringstream ss;
    if (!isAnimation)
        ss << ASSET_PATH << "Sprites/" << spriteName << ".txt";
    else ss << spriteName;

    ifstream file = tryOpenFile(ss.str());

    string buffer;

    getline(file,buffer);

    vector<string> splString  = string_split(buffer,' ');

    if (splString.size() != 2)
        throw std::runtime_error("Ficheiro de sprite inválido!");

    Vector2 size(stoi(splString[0]), stoi(splString[1]));

    auto pixelMatrix = new short [size.getX() * size.getY()];

    while (!file.eof())
    {
        getline(file,buffer);
        splString  = string_split(buffer,' ');

        if (splString.size() != 3)
            continue;

        int x = stoi(splString[0]);
        int y = stoi(splString[1]);
        short color = stos(splString[2]);

        pixelMatrix[(y * (size.getX())) + x] = color;
    }

    if (isAnimation)
    {
        auto sprName = string_split(spriteName,'/').back();
        sprName = sprName.substr(0,sprName.size() - 4);
        spritePool.insert(pair<string,SpriteContainer>(sprName,SpriteContainer(pixelMatrix,size)));
    }
    else spritePool.insert(pair<string,SpriteContainer>(spriteName,SpriteContainer(pixelMatrix,size)));

    file.close();
}

SpriteContainer AssetManager::getSprite(const string& spriteName)
{
    if (!spritePool.contains(spriteName))
        tryLoadSprite(spriteName,false);

    return spritePool[spriteName];
}

AssetManager *AssetManager::getInstance()
{
    if (instance == nullptr)
        instance = new AssetManager();
    return instance;
}

void AssetManager::kill()
{
    for (auto pair : spritePool)
        delete[] pair.second.getPixelMatrix();

    delete instance;
}

map<char, Sprite> AssetManager::getAnimation(const string& animName)
{
    if (!animPool.contains(animName))
        tryLoadAnimation(animName);

    return animPool[animName];
}

void AssetManager::tryLoadAnimation(const string &animName)
{
    map<char,Sprite> temp;
    stringstream ss;
    ss << ASSET_PATH << "Animations/" << animName;
    for(const auto& it : filesystem::directory_iterator(ss.str()))
    {
        tryLoadSprite(it.path().string(), true);
        auto spriteName = string_split(it.path().string(),'/').back();
        spriteName = spriteName.substr(0,spriteName.size() - 4);
        Sprite spr(spriteName);
        spriteName = spriteName.substr(spriteName.size() - 2,spriteName.size() - 1);
        char c = (char) stos(spriteName);
        temp.insert(pair<char,Sprite>(c,spr));
    }
    animPool.insert(pair<string,map<char,Sprite>>(animName,temp));
}

ifstream AssetManager::tryOpenFile(const string& fileName)
{
    if (!filesystem::exists(fileName))
        throw runtime_error("Ficheiro não encontrado!");

    ifstream file(fileName);

    if (!file.is_open())
        throw runtime_error("Não foi possivel abrir o ficheiro!");

    return file;
}

bool AssetManager::getConfig(const string& configName)
{
    if (gameConfigs.contains(configName))
        return gameConfigs[configName];

    stringstream ss;
    ss << ASSET_PATH << "config.txt";
    ifstream file = tryOpenFile(ss.str());

    string buffer;

    while(!file.eof())
    {
        getline(file,buffer);
        vector<string> spl = string_split(buffer,':');
        if (spl.size() != 2)
            continue;
        gameConfigs.insert(pair<string,bool>(spl[0], stob(spl[1])));
    }

    file.close();

    if (gameConfigs.contains(configName))
        return gameConfigs[configName];

    throw invalid_argument("Não foi encontrada uma configuração com o nome " + configName);

}

int AssetManager::getEnemyScore(const string &enemyName)
{
    if (enemyScoreBuff.contains(enemyName))
        return enemyScoreBuff[enemyName];

    stringstream ss;
    ss << ASSET_PATH << "enemyRatios.txt";
    ifstream file = tryOpenFile(ss.str());
    string buffer;

    while(!file.eof())
    {
        getline(file,buffer);
        auto spl = string_split(buffer,':');
        if (spl.size() != 2)
            continue;
        enemyScoreBuff.insert(pair<string,int>(spl[0], stoi(spl[1])));
    }

    if (!enemyScoreBuff.contains(enemyName))
        throw runtime_error("Inimigo não encontrado!");

    return enemyScoreBuff[enemyName];
}

vector<ShipContainer> AssetManager::getSpaceShips()
{
    if (!shipData.empty())
        return shipData;

    stringstream ss;
    ss << ASSET_PATH << "spaceShips.txt";
    ifstream file = tryOpenFile(ss.str());
    string buffer;

    while(!file.eof())
    {
        getline(file,buffer);
        auto spl =   string_split(buffer,';');
        if (spl.size()!=4)
            continue;
        ShipContainer sc(spl[1],spl[0],spl[2],stof(spl[3]));
        shipData.push_back(sc);
    }

    if (shipData.empty())
        throw runtime_error("Nenhuma nave encontrada");

    return shipData;

}

