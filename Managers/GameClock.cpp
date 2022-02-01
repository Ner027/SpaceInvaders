#include "GameClock.h"
#include "../Util/Constants.h"

GameClock* GameClock::instance = nullptr;


//Assim como o gestor de recursos, o relógio do jogo também segue um padrão Singleton
GameClock *GameClock::getInstance()
{
    if (instance == nullptr)
        instance = new GameClock();
    return instance;
}


using namespace std::chrono;
///Loop que trata a lógica do jogo,roda numa thread separada
void GameClock::gameLoop()
{
    while (keepRunning)
    {
        //Guardar o tempo onde o tick começou
        auto startTime = high_resolution_clock::now();

        //Iterar a lista de objectos
        for (auto it = tickObjects.cbegin();it != tickObjects.cend();)
        {
            auto tObj = *it;

            //Se o objecto tem um componente de colisões testar as colisões com os objectos registados
            if (tObj->colliderComponent)
            {
                for (auto c: registeredCollisionObjects)
                {
                    //Se estiverem a colidir fazer com que o objecto trate a colisão
                    if (c->isColliding(tObj) && c->selfId != tObj->selfId)
                        tObj->colliderComponent->onCollision(tObj, c);

                }
            }

            //Se este objecto estiver marcado para ser destruido
            if (tObj->markedForDelete)
            {
                //Remover da lista de colisões
                unregisterForCollisions(tObj);
                //Remover dos objectos de jogo
                tickObjects.erase(it);
                //Libertar a memória do object
                delete tObj;
            }
            else
            {
                tObj->tick(currentTick); //Caso contrário executar o tick no objecto
                ++it;
            }
        }

        //O jogo roda num ciclo de ticks definido, caso tenha chegado ao fim do ciclo resetar o esmo
        if (currentTick != TICK_CYCLE + 1)
            currentTick++;
        else currentTick = 0;

        /*Para manter um tick rate constante, independemente do tempo de execução do tick esperar ate completar
         * o tempo definido, caso já tenha demorado mais que o tamanho de um tick, simplesmente continua*/

        while(duration_cast<microseconds>(high_resolution_clock::now() - startTime).count() <= TICK_TIME_US);

    }
}

void GameClock::startGameClock()
{
    keepRunning = true;
    //Começa o relógio do jogo criando uma thread para o mesmo
    gameThread = thread(&GameClock::gameLoop, this);
    //Rodar a thread separada da thread principal
    gameThread.detach();
}

/// Regista um novo objecto no relógio do jogo
/// \param object Objecto a registar
void GameClock::registerObject(GameObject* object)
{
    //Para evitar problemas de concorrencia é travado o acesso a outras threads enquanto esta executa
    gameMutex.lock();
    object->selfId = currentIdentifier++;
    tickObjects.push_back(object);
    gameMutex.unlock();
}

/// Registar um objecto para colisões
/// \param tObj Objecto a registar
void GameClock::registerForCollisions(GameObject* tObj)
{
    gameMutex.lock();
    for (auto o : registeredCollisionObjects)
        if (o->selfId == tObj->selfId)
            return;
    /*Se já existe um object com este ID registado retornar
     * caso contrário inserir na lista de objectos*/
    registeredCollisionObjects.push_back(tObj);
    gameMutex.unlock();
}

/// Remove um objecto da lista de colisões
/// \param obj Objecto a remover da lista de colisões
void GameClock::unregisterForCollisions(GameObject *obj)
{
    for (int i = 0; i < registeredCollisionObjects.size(); ++i)
    {
        //Procurar um objecto com o ID desejado
        if (obj->selfId == registeredCollisionObjects[i]->selfId)
        {
            //Quando achar apagar e retornar
            registeredCollisionObjects.erase(registeredCollisionObjects.cbegin() + i);
            return;
        }
    }
}

///Metodo que apaga todos os objetos de jogo registados no momento
void GameClock::killAll()
{
    gameMutex.lock();
    for (auto go : tickObjects)
        go->markedForDelete = true;
    gameMutex.unlock();
}

void GameClock::destroyInstance()
{
    delete instance;
    instance = nullptr;
}

GameClock::~GameClock()
{
    keepRunning = false;
}
