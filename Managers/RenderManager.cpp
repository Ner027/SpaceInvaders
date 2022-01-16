#include <ncurses.h>
#include "RenderManager.h"

RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager()
{
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
    init_pair(9,COLOR_BLACK,COLOR_WHITE);
}

///
/// \return Instância unica do RenderManager
RenderManager *RenderManager::getInstance()
{
    if (instance == nullptr)
        instance = new RenderManager();
    return instance;
}

void RenderManager::renderLoop()
{
    while (true)
    {
        short kp = getch();
        if (kp != ERR)
            inputQueue.push(kp);

        if (renderQueue.empty())
            continue;

        auto object = renderQueue.front();
        if (object->toDraw)
            object->drawInternal();
        else object->eraseInternal();
        delete object;
        wrefresh(gameWindow);
        renderQueue.pop();
    }
}

void RenderManager::startRendering()
{
    renderThread = thread(&RenderManager::renderLoop,this);
    renderThread.detach();
}

void RenderManager::enqueueRenderAction(ScreenObject* object)
{
    renderMutex.lock();
    renderQueue.push(object);
    renderMutex.unlock();
}

WINDOW *RenderManager::getWindow()
{
    return gameWindow;
}

void RenderManager::queueInput(short s)
{
    renderMutex.lock();
    inputQueue.push(s);
    renderMutex.unlock();
}

short RenderManager::getFirstKeyPressed()
{
    short temp = ERR;
    renderMutex.lock();
    if (!inputQueue.empty())
    {
        temp = inputQueue.front();
        inputQueue.pop();
    }
    renderMutex.unlock();
    return temp;
}