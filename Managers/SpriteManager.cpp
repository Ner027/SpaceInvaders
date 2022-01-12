#include "SpriteManager.h"
#include "../Util/Constants.h"
#include "../Util/Util.h"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "../CursesWrapper/Vector2.h"

SpriteManager* SpriteManager::instance = nullptr;

void SpriteManager::tryLoadSprite(const string& spriteName)
{
    string fullPath = SPRITE_PATH + spriteName + ".txt";

    if (!filesystem::exists(fullPath))
        throw runtime_error("Ficheiro não encontrado!");

    ifstream file(fullPath);

    if (!file.is_open())
        throw runtime_error("Não foi possivel abrir o ficheiro!");

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

    spritePool.insert(pair<string,SpriteContainer>(spriteName,SpriteContainer(pixelMatrix,size)));

    file.close();
}

SpriteContainer SpriteManager::getSprite(const string& spriteName)
{
    if (spritePool.contains(spriteName))
        return spritePool[spriteName];

    tryLoadSprite(spriteName);

    return spritePool[spriteName];
}

SpriteManager *SpriteManager::getInstance()
{
    if (instance == nullptr)
        instance = new SpriteManager();
    return instance;
}

void SpriteManager::kill()
{
    for (auto pair : spritePool)
        delete[] pair.second.getPixelMatrix();

    delete instance;
}

