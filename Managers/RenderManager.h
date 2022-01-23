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
    void renderLoop();
    atomic<bool> shouldClear = false;
    atomic<bool> keepRunning = false;
    void drawBox();
    ~RenderManager();
public:
    static RenderManager* getInstance();
    void enqueueRenderAction(ScreenObject* object);
    void startRendering();
    short getFirstKeyPressed();
    void clearScreen();
    void clearInputQueue();
    static void destroyInstance();

};


#endif
