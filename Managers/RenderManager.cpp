#include <ncurses.h>
#include "RenderManager.h"
#include "../Util/Constants.h"

RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager()
{
    //Inicializar tudo relacionado ao Curses
    initscr();

    raw();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    start_color();
    curs_set(0);

    init_pair(1,COLOR_BLACK,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_RED);
    init_pair(3,COLOR_GREEN,COLOR_GREEN);
    init_pair(4,COLOR_YELLOW,COLOR_YELLOW);
    init_pair(5,COLOR_BLUE,COLOR_BLUE);
    init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(7,COLOR_CYAN,COLOR_CYAN);
    init_pair(8,COLOR_WHITE,COLOR_WHITE);
    init_pair(9,COLOR_WHITE,COLOR_BLACK);

    //Para o jogo poder operar corretamente é necessário um tamanho minimo no terminal
    if (COLS < GW_X || LINES < GW_Y)
        throw runtime_error("O terminal não tem o tamanho necessário!");


}

RenderManager *RenderManager::getInstance()
{
    if (instance == nullptr)
        instance = new RenderManager();
    return instance;
}

///Loop que trata da renderização de objectos para o ecrã,corre numa thread própria
[[noreturn]] void RenderManager::renderLoop()
{
    while (true)
    {
        //Caso queira limpar o ecrã
        if (shouldClear)
        {
            /*Devido ás limitações do Curses não é possível efetuar operações no ecrã
             * de duas threads diferentes então é necessário isto*/
            clear();
            shouldClear = false;
            continue;
        }
        //Pela mesma razão do clear,a input tem de ser tratada nesta thread

        //Ler o caracter
        short kp = getch();
        //Se for um caracter valido colocar na fila de entrada
        if (kp != ERR)
            inputQueue.push(kp);

        //Senão houver nada para renderizar volta ao início do loop
        if (renderQueue.empty())
            continue;

        //Caso contrário é usado o primeiro elemento na fila
        auto object = renderQueue.front();
        //Dependendo da operação, apagar ou desenhar
        if (object->toDraw)
            object->drawInternal();
        else object->eraseInternal();
        //Após efetuar a operação libertar a memória do objecto
        delete object;
        //Dar refresh ao ecrã
        refresh();
        //Remover a frente da fila
        renderQueue.pop();
    }
}

///Metodo que começa o loop de renderização
void RenderManager::startRendering()
{
    //Assim como o GameClock este também roda numa thread própria em modo separado
    renderThread = thread(&RenderManager::renderLoop,this);
    renderThread.detach();
}

///Adiciona uma ação de renderização á fila
void RenderManager::enqueueRenderAction(ScreenObject* object)
{
    //Para evitar problemas de concurrencia, travar a thread
    renderMutex.lock();
    renderQueue.push(object);
    renderMutex.unlock();
}

/// Obtem a tecla carregada em primeiro lugar
/// \return Primeira tecla na fila de entrada
short RenderManager::getFirstKeyPressed()
{
    short temp = ERR;
    renderMutex.lock();
    if (!inputQueue.empty())
    {
        temp = inputQueue.front();
        inputQueue.pop();
        //Após obter a tecla remover da frente da file
    }
    renderMutex.unlock();
    return temp;
}


void RenderManager::destroyInstance()
{
    delete instance;
    instance = nullptr;
}

void RenderManager::clearScreen()
{
    shouldClear = true;
}
