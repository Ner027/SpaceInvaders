#ifndef SPACEINVADERS_RENDERMANAGER_H
#define SPACEINVADERS_RENDERMANAGER_H
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include "../CursesWrapper/ScreenObject.h"

using namespace std;
class RenderManager
{
private:
    thread renderThread;
    mutex renderMutex;
    queue<ScreenObject*> renderQueue;
    queue<short> inputQueue;
    static RenderManager* instance;
    RenderManager();
    [[noreturn]] void renderLoop();
public:
    static RenderManager* getInstance();
    void enqueueRenderAction(ScreenObject* object);
    void startRendering();
    short getFirstKeyPressed();
    atomic<bool> shouldClear;

};


#endif
