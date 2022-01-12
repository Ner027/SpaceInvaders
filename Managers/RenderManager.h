#ifndef SPACEINVADERS_RENDERMANAGER_H
#define SPACEINVADERS_RENDERMANAGER_H
#include <thread>
#include <mutex>
#include <queue>
#include "../CursesWrapper/IScreenObject.h"

using namespace std;
class RenderManager
{
private:
    thread renderThread;
    mutex renderMutex;
    queue<IScreenObject*> renderQueue;
    static RenderManager* instance;
    RenderManager();
    [[noreturn]] void renderLoop();
public:
    static RenderManager* getInstance();
    void enqueueRenderAction(IScreenObject* object);
    void startRendering();
};

#endif
