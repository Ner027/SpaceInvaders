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
    clear();

    init_pair(1,COLOR_BLACK,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_RED);
    init_pair(3,COLOR_GREEN,COLOR_GREEN);
    init_pair(4,COLOR_YELLOW,COLOR_YELLOW);
    init_pair(5,COLOR_BLUE,COLOR_BLUE);
    init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(7,COLOR_CYAN,COLOR_CYAN);
    init_pair(8,COLOR_WHITE,COLOR_WHITE);

    bkgd(COLOR_PAIR(1));
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
        if (renderQueue.empty())
            continue;

        auto object = renderQueue.front();
        if (object->toDraw)
            object->drawInternal();
        else object->eraseInternal();
        delete object;
        refresh();
        renderQueue.pop();
    }
}

void RenderManager::startRendering()
{
    renderThread = thread(&RenderManager::renderLoop,this);
    renderThread.detach();
}

void RenderManager::enqueueRenderAction(IScreenObject* object)
{
    renderMutex.lock();
    renderQueue.push(object);
    renderMutex.unlock();
}
