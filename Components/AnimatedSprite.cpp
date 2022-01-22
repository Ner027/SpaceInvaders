#include "AnimatedSprite.h"
#include "../Managers/AssetManager.h"


void AnimatedSprite::execute(char curTick)
{
    /*Caso as animações estejam desabilitadas e o primeiro frame já tenha sido
     * renderizado, o componente não deve executar mais nada*/

    if (!animationsEnabled && currentFrame != -1)
        return;


    if (!frames.contains(curTick))
        return;

    /*Caso seja o primeiro frame a ser desenhado no ecrã não é necessário
     * apagar o frame anterio*/

    if (currentFrame == -1)
    {
        currentFrame = curTick;
        frames.find(curTick)->second.draw();
    }
    else
    {
        //Caso haja algum frame desenhado, primeiro apagar e só depois desenhar o atual
        frames.find(currentFrame)->second.erase();
        frames.find(curTick)->second.draw();
        currentFrame = curTick;
    }
}

void AnimatedSprite::exitCleanly()
{
    //Ao ser destruido apagar do ecrã o frame atual
    if (frames.contains(currentFrame))
        frames.find(currentFrame)->second.erase();
}

void AnimatedSprite::moveBy(const Vector2 &df)
{
    /*Quando este componente for movido é necessário mover todos os frames
     * que compõe a animação*/

    for (auto& pair : frames)
        pair.second.moveBy(df);
    //TODO:Verificar se isto é necessário
    if (frames.contains(currentFrame))
        frames.find(currentFrame)->second.draw();
}

void AnimatedSprite::moveTo(const Vector2 &nPos)
{
    //Comportamento semelhante ao moveBy, apenas move termos de posição absoluta
    for(auto& pair : frames)
        pair.second.moveTo(nPos);
    if (frames.contains(currentFrame))
        frames.find(currentFrame)->second.draw();
}


///
/// \return Retorna o tamanho do frame atual,caso nenhum tenha sido renderizado ainda retorna o tamanho do primeiro frame
Vector2 AnimatedSprite::getSize()
{
    if (!frames.contains(currentFrame))
        return frames.begin()->second.getSize();
    return frames.find(currentFrame)->second.getSize();
}

///
/// \return Retorna a posição do frame atual,caso nenhum tenha sido renderizado retorna a posição do primeiro
Vector2 AnimatedSprite::getPosition()
{
    if (!frames.contains(currentFrame))
        return frames.begin()->second.getPosition();
    return frames.find(currentFrame)->second.getPosition();
}

///
/// \return Retorna o Sprite do frame atual,caso nenhum tenha sido renderizado retorna o primeiro
Sprite AnimatedSprite::getCurrentSprite()
{
    if (!frames.contains(currentFrame))
        return frames.begin()->second;
    return frames.find(currentFrame)->second;
}

AnimatedSprite::AnimatedSprite(const string& name)
{
    auto assetManager = AssetManager::getInstance();
    //Inicializar o mapa dos frames
    this->frames = assetManager->getAnimation(name);
    //Obter do ficheiro de configurações o estado das animações
    this->animationsEnabled = assetManager->getConfig("animationsEnabled");
}

void AnimatedSprite::onAdd() {}


