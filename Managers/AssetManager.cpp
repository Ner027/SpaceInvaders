#include "AssetManager.h"
#include "../Util/Constants.h"
#include "../Util/Util.h"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "../CursesWrapper/Sprite.h"
#include <iostream>
AssetManager* AssetManager::instance = nullptr;

/// Tenta carregar um Sprite a partir de um ficheiro
/// \param spriteName Nome do sprite a tentar carregar
/// \param isAnimation Se é um ficheiro de animação ou normal
void AssetManager::tryLoadSprite(const string& spriteName,bool isAnimation)
{

    //Formar o caminho para o ficheiro
    stringstream ss;
    if (!isAnimation)
        ss << ASSET_PATH << "Sprites/" << spriteName << ".txt";
    else ss << spriteName;

    //Tentar abrir o ficheiro
    ifstream file = tryOpenFile(ss.str());

    string buffer;

    //Ler a primeira linha do ficheiro
    getline(file,buffer);

    //Separar a linha no caracter ' '
    vector<string> splString  = string_split(buffer,' ');

    //Se o resultante da separação não forem 2 elementos o ficheiro é inválido
    if (splString.size() != 2)
        throw std::runtime_error("Ficheiro de sprite inválido!");

    //Tentar converter os valores para inteiros que representam o tamanho em X e Y do Sprite
    Vector2 size(stoi(splString[0]), stoi(splString[1]));

    //Alocar espaço para todos os "blocos" do Sprite
    auto pixelMatrix = new short [size.getX() * size.getY()];

    //Enquanto não chegar ao fim do ficheiro
    while (!file.eof())
    {
        //Ler a linha e separar no caracter ' '
        getline(file,buffer);
        splString  = string_split(buffer,' ');

        //Se não tiver tamanho 3 ignorar
        if (splString.size() != 3)
            continue;

        //Senão tentar converter para valores de X, Y e cor do bloco
        int x = stoi(splString[0]);
        int y = stoi(splString[1]);
        short color = stos(splString[2]);

        //Matriz em forma linear, cada linha é colocada em frente a última
        pixelMatrix[(y * (size.getX())) + x] = color;
    }

    //Dividir o nome dependendo se é um ficheiro de animação ou normal
    if (isAnimation)
    {
        auto sprName = string_split(spriteName,'/').back();
        sprName = sprName.substr(0,sprName.size() - 4);
        spritePool.insert(pair<string,SpriteContainer>(sprName,SpriteContainer(pixelMatrix,size)));
    }
    else spritePool.insert(pair<string,SpriteContainer>(spriteName,SpriteContainer(pixelMatrix,size)));

    //Fechar o ficheiro
    file.close();
}

SpriteContainer AssetManager::getSprite(const string& spriteName)
{
    //Se o Sprite requerido ainda não estiver carregado tentar carregar
    if (!spritePool.contains(spriteName))
        tryLoadSprite(spriteName,false);

    //Caso contrário retornar o Sprite ja carregado
    return spritePool[spriteName];
}

//O gestor de recursos é mantido como uma instância única (Singleton) para evitar cópias desnecessárias
AssetManager *AssetManager::getInstance()
{
    if (instance == nullptr)
        instance = new AssetManager();
    return instance;
}

map<char, Sprite> AssetManager::getAnimation(const string& animName)
{
    //Semalhante ao "getSprite", mas para animações
    if (!animPool.contains(animName))
        tryLoadAnimation(animName);

    return animPool[animName];
}

///
/// \param animName Nome da animação a tentar carregar
void AssetManager::tryLoadAnimation(const string &animName)
{
    /*Os frames de cada animação são guardados num mapa para agilizar
     * o processo de procura dos mesmos durante as animações*/

    //Criar o caminho onde estão os ficheiros da animação
    map<char,Sprite> temp;
    stringstream ss;
    ss << ASSET_PATH << "Animations/" << animName;

    //Iterar por todos os ficheiros presentes nessa pasta
    for(const auto& it : filesystem::directory_iterator(ss.str()))
    {
        //Tentar carregar o Sprite com esse nome
        tryLoadSprite(it.path().string(), true);
        //O nome do sprite é a última parte do caminho
        auto spriteName = string_split(it.path().string(),'/').back();
        //Remover o tipo do ficheiro (.txt), do nome
        spriteName = spriteName.substr(0,spriteName.size() - 4);
        //Criar um Sprite deste tipo
        Sprite spr(spriteName);
        //Obter o número do frame do Sprite
        spriteName = spriteName.substr(spriteName.size() - 2,spriteName.size() - 1);
        char c = (char) stos(spriteName);
        //Inserir no mapa de frames
        temp.insert(pair<char,Sprite>(c,spr));
    }
    //Após carregar a animção, inserir no mapa de animações
    animPool.insert(pair<string,map<char,Sprite>>(animName,temp));
}

/// Metodo auxiliar para fazer as verificações necessárias ao abrir ficheiros
/// \param fileName Nome do ficheiro a tentar abrir
/// \return Stream de entrada do ficheiro
ifstream AssetManager::tryOpenFile(const string& fileName)
{
    if (!filesystem::exists(fileName))
        throw runtime_error("Ficheiro não encontrado!");

    ifstream file(fileName);

    if (!file.is_open())
        throw runtime_error("Não foi possivel abrir o ficheiro!");

    return file;
}

///
/// \param configName Nome da configuração a procurar
/// \return Valor lógico da configuração
bool AssetManager::getConfig(const string& configName)
{
    //Se o mapa de configurações já contem esta configuração retornar a mesma
    if (gameConfigs.contains(configName))
        return gameConfigs[configName];

    //Caso contrário tentar carregar todas as configurações do ficheiro de configuração
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

    //Se após carregar as configurações o mapa já contém a configuração retornar a mesma
    if (gameConfigs.contains(configName))
        return gameConfigs[configName];

    //Caso contrário lançar uma excepção
    throw invalid_argument("Não foi encontrada uma configuração com o nome " + configName);

}

///
/// \param enemyName Nome do inimigo
/// \return Valor da score que este dá quando morto
int AssetManager::getEnemyScore(const string &enemyName)
{
    //Mesmo processo que as configurações

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

/// Metodo que tenta carregar as naves disponíveis no jogo
/// \return Lista de naves
vector<ShipContainer> AssetManager::getSpaceShips()
{
    //Se já tiverem sido carregada retornar as mesmas
    if (!shipData.empty())
        return shipData;

    //Caso contrário tentar carregar
    stringstream ss;
    ss << ASSET_PATH << "spaceShips.txt";
    ifstream file = tryOpenFile(ss.str());
    string buffer;

    while(!file.eof())
    {
        getline(file,buffer);
        auto spl =   string_split(buffer,';');
        if (spl.size()!=6)
            continue;
        ShipContainer
        sc(spl[1],spl[0],spl[2],
                         stof(spl[3]), stol(spl[4]), stos(spl[5]));
        shipData.push_back(sc);
    }

    //Se nenhuma nave for encontrada lançar uma excepção
    if (shipData.empty())
        throw runtime_error("Nenhuma nave encontrada");

    return shipData;
}

AssetManager::~AssetManager()
{
    for(auto& pair : spritePool)
        delete [] pair.second.getPixelMatrix();
}

void AssetManager::destroyInstance()
{
    delete instance;
    instance = nullptr;
}
