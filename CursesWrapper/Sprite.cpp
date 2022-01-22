#include "Sprite.h"
#include <vector>
#include "../Managers/RenderManager.h"
#include "../Managers/AssetManager.h"

void Sprite::draw()
{
    toDraw = true;
    auto copy = new Sprite(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void Sprite::erase()
{
    toDraw = false;
    auto copy = new Sprite(*this);
    RenderManager::getInstance()->enqueueRenderAction(copy);
}

void Sprite::eraseInternal()
{
    //Para apagar iterar pelo tamanho do Sprite e colocar um caracter com a cor do background
    attron(COLOR_PAIR(1));
    for (int i = 0; i < internalSize.getY() ; ++i)
        for (int j = 0; j < internalSize.getX(); ++j)
            mvprintw(i + localPosition.getY(),localPosition.getX() + j * 2,"  ");
    attroff(COLOR_PAIR(1));

}

void Sprite::drawInternal()
{
    //Iterar a matriz de cores do Sprite
    for (int i = 0; i < internalSize.getY() ; ++i)
    {
        for (int j = 0; j < internalSize.getX(); ++j)
        {
            short color = pixelMatrix[(i * (internalSize.getX())) + j];
            //Ligar a cor
            attron(COLOR_PAIR(color));
            //Colocar o caracter
            mvprintw(i + localPosition.getY(),localPosition.getX() + j * 2,"  ");
            //Desligar a cor
            attroff(COLOR_PAIR(color));
        }
    }
}

Sprite::Sprite(const std::string& name) : ScreenObject({0,0},{0,0}), internalSize(0,0)
{
    this->spriteName = name;
    //Obter a matriz de cores do gestor de recursos para evitar copiar a matriz para cada sprite
    auto sCont = AssetManager::getInstance()->getSprite(name);
    this->pixelMatrix = sCont.getPixelMatrix();
    this->internalSize = sCont.getSize();
    /*Como os caracteres da consola são rectangulares, cada "bloco" de cor corresponde a 2 caracteres
     * então existe um tamanho interno referente ao tamanho da matriz de cores e outro tamanho para tudo externo
     * ao próprio sprite*/
    this->size = {internalSize.getX() * 2,internalSize.getY()};

}


Sprite::Sprite(const Sprite& og) : ScreenObject(og.localPosition,og.size), internalSize(og.internalSize)
{
    localPosition = og.localPosition;
    toDraw = og.toDraw;
    pixelMatrix = og.pixelMatrix;
}

void Sprite::moveTo(const Vector2 &nPos)
{
    //Antes de mover primeiro apagar o atual
    this->erase();
    //Mudar a posição
    this->localPosition = nPos;
    //Voltar a desenhar
    this->draw();
}

//Semelhante ao "moveTo", mas para deslocamentos em vez de posiçoes abosulutas
void Sprite::moveBy(const Vector2 &df)
{
    this->erase();
    this->localPosition += df;
    this->draw();
}

const std::string &Sprite::getName()
{
    return this->spriteName;
}

const short *Sprite::getPixelMatrix()
{
    return this->pixelMatrix;
}
