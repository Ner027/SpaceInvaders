#include <vector>
#include "GameManager.h"
#include "../Components/EnemyAI.h"
#include "../Components/Physics.h"
#include "../Util/Constants.h"
#include "GameClock.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "../Util/Util.h"
#include "../CursesWrapper/BigTextBox.h"
#include <cmath>
#include <sstream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
    //Por default usar a primeira nave disponível
    playerShip = new ShipContainer(AssetManager::getInstance()->getSpaceShips().front());
}

//Singleton
GameManager *GameManager::getInstance()
{
    if (instance == nullptr)
        instance = new GameManager();
    return instance;
}

///Controlo principal da ógica principal do jogo
void GameManager::gameControllerLoop()
{
    RenderManager* rm = RenderManager::getInstance();
    using namespace std::chrono;
    //Ultimo vez que o player disparou, inicializada com o tempo atual
    auto lastFire = high_resolution_clock::now();
    //Tempo entre disparos
    long fireR = playerShip->fireRate;

    while (shouldRun)
    {
        int kp = rm->getFirstKeyPressed();
        switch (kp)
        {
            case KEY_LEFT:
                player->setVelocity(-playerShip->velocity,0,2);
                break;
            case KEY_RIGHT:
                player->setVelocity(playerShip->velocity,0,2);
                break;
                //Quando clicar no espaço
            case ' ':
                //Verificar se já passou o tempo de delay desde o ultimo disparo
                if (duration_cast<milliseconds>(high_resolution_clock::now() - lastFire).count() >= fireR)
                {
                    //Disprar a bala
                    shootBullet();
                    //Definir o tempo do último disparo como o tempo atual
                    lastFire = high_resolution_clock::now();
                }
                break;
                //Ao clicar para cima ou para baixo parar o jogador
            case KEY_DOWN:
            case KEY_UP:
                player->setVelocity(0,0,1);
                break;
            default:
                break;
        }
    }
    postLevelCleanup();
}

void GameManager::startGame()
{
    mainMenu();
}

void GameManager::addScore(int i)
{
    //Se o jogo não estiver a correr não adicionar score
    if (!shouldRun)
        return;
    this->score += i;
    //Atualizar o texto da score
    scoreBox.changeText("Score: " + to_string(score));
}

void GameManager::endCurrentLevel()
{
    shouldRun = false;
}

void GameManager::startCurrentLevel()
{
    shouldRun = true;
    scoreBox.changeText("Score: " + to_string(score));
    scoreBox.moveTo({5,GW_Y + 2});

    livesBox.changeText("Lives: " + to_string(playerLives));
    livesBox.moveTo({GW_X - 13,GW_Y + 2});

    //Criar objecto de controlo dos inimigos
    enemyCtl = GameObject::Instantiate();

    //Dependendo do nivel colocar os inimigos correctos
    vector<string> enemyNames;
    switch (currentLevel)
    {
        case 0:
            enemyNames = {"enemy_basic"};
            break;
        case 1:
            enemyNames = {"enemy_medium","enemy_basic"};
            break;
        case 2:
            enemyNames = {"enemy_hard","enemy_medium","enemy_basic"};
            break;
        default:
            break;
    }
    //Componente de controlo dos inimigos
    EnemyAI enemyAi(enemyNames);
    enemyCtl->addComponent(enemyAi);

    //Criar o player
    player = GameObject::Instantiate();
    SpriteRenderer playerSkinRenderer(playerShip->spriteName);
    player->addComponent(playerSkinRenderer);
    //Clocar o player no local correto
    player->moveTo(Vector2(GW_X/2,GW_Y - 2)
    - Vector2(player->getSize().getX()/2,player->getSize().getY()));

    //Adicionar ao player um componente de físicas
    Physics ph(player,0,0);
    player->addComponent(ph);
    //Habilitar as colisões no player
    if (!AssetManager::getInstance()->getConfig("godMode"))
        player->setCollisionTester(BETTER_BOUNDING_BOX);
    //Criar as barreiras
    createBarriers();
    //Entrar no loop de controlo do jogo
    gameControllerLoop();
}

///Dispara uma bala proveniente do jogador
void GameManager::shootBullet()
{
    //Criar objecto da bala e adicionar-lhe o componente de renderização
    auto bulletObject = GameObject::Instantiate();
    SpriteRenderer spriteRenderer("bullet");
    bulletObject->addComponent(spriteRenderer);

    //Mover a bala para a frente do jogador
    bulletObject->moveTo({player->getPosition().getX() + (player->getSize().getX() / 2) - 1
                          ,player->getPosition().getY() - 2});
    Bullet bullet(player);
    //Adicionar a bala um componente de físicas com uma velocidade negativa no eixo Y
    Physics bulletPhysics(bulletObject,0,-BULLET_SPEED);
    bulletObject->addComponent(bullet);
    bulletObject->addComponent(bulletPhysics);
    bulletObject->setFlag("playerBullet",true);
    //Ativar as colisões na bala
    bulletObject->setCollisionTester(BETTER_BOUNDING_BOX);
}
///
/// \return Retorna o ID do jogo correspondente ao player
long GameManager::getPlayerId() const
{
    return player->getId();
}

///Termina o jogo
void GameManager::gameOver()
{
    currentLevel = 0;
    //Colocar no ecrã o desenho de GameOver
    RenderManager* rm = RenderManager::getInstance();
    Sprite spr("gameover");
    spr.moveTo(centerToScreen(&spr));

    //Esperar que o jogador clique na barra de espaços
    while (true)
    {
        int kp = rm->getFirstKeyPressed();
        if (kp == ' ')
            break;
    }
    //Apagar o desenho
    spr.erase();
    //Voltar ao menu
    mainMenu();
}

///Criar as 3 barreiras
void GameManager::createBarriers()
{
    createSingleBarrier({11,GW_Y - 25});
    createSingleBarrier({GW_X - 52,GW_Y - 25});
    createSingleBarrier({(GW_X/2) - 20,GW_Y  - 25});
}

void GameManager::createSingleBarrier(const Vector2& position)
{
    //Cada barreira é composta por blocos
    SpriteRenderer sprite("block");
    for (int i = position.getY(); i < position.getY() + 5; ++i)
    {
        for (int j = position.getX(); j < position.getX() + 40; j+=2)
        {
            //Criar esses blocos
            auto go = GameObject::Instantiate();
            go->addComponent(sprite);
            //Registar os blocos para colisões
            go->setCollisionTester(BETTER_BOUNDING_BOX);
            go->moveTo({j,i});
        }
    }
}

void GameManager::winCurrentLevel()
{
    //Se não for o último nível, ir para o próximo
    if (currentLevel != 2)
    {
        currentLevel++;
    }
    else
    {
        RenderManager::getInstance()->clearScreen();
        GameClock::getInstance()->killAll();
        AssetManager::getInstance()->insertScore(playerName,score);
        BigTextBox textBox("You are the champion\nFinal Score\n" + to_string(score),{0,0});
        textBox.moveTo(centerToScreen(&textBox));
        this_thread::sleep_for(3s);
        RenderManager::getInstance()->clearScreen();
        mainMenu();
    }
    GameClock::getInstance()->killAll();
    RenderManager::getInstance()->clearScreen();
    hasWon = true;
    shouldRun = false;
}

void GameManager::shipSelectionMenu()
{
    int index = 0;
    int posY;
    vector<ShipContainer> availableShips = AssetManager::getInstance()->getSpaceShips();
    RenderManager* rm = RenderManager::getInstance();
    Sprite ship(playerShip->spriteName);
    TextBox desc(getShipDescription(*playerShip),{0,0},9);
    ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
    posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
    desc.moveTo({centerToScreen(&desc).getX(),posY});

    while(true)
    {
        short kp = rm->getFirstKeyPressed();

        switch (kp)
        {
            case ' ':
                ship.erase();
                desc.erase();
                return;
            case KEY_RIGHT:
                delete playerShip;
                playerShip = new ShipContainer(availableShips[(index++)%availableShips.size()]);
                ship.erase();
                ship = Sprite(playerShip->spriteName);
                ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
                posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
                desc.changeText(getShipDescription(*playerShip));
                desc.moveTo({centerToScreen(&desc).getX(),posY});
                break;
            case KEY_LEFT:
                delete playerShip;
                playerShip = new ShipContainer(availableShips[(index--)%availableShips.size()]);
                ship.erase();
                ship = Sprite(playerShip->spriteName);
                ship.moveTo(centerToScreen(&ship) + Vector2::Up().multiplyBy(4));
                posY = ship.getSize().getY() + ship.getPosition().getY() + 1;
                desc.changeText(getShipDescription(*playerShip));
                desc.moveTo({centerToScreen(&desc).getX(),posY});
                break;
            default:
                break;
        }
    }
}

void GameManager::postLevelCleanup()
{
    shouldRun = false;
    GameClock::getInstance()->killAll();
    this_thread::sleep_for(0.5s);
    RenderManager::getInstance()->clearInputQueue();
    scoreBox.erase();
    livesBox.erase();

    string text;
    if (!hasWon)
    {
        if(--playerLives == 0)
            gameOver();
        text = to_string(playerLives)  + "\nHP\nLeft";
    }
    else
    {
        text = "You Won\nScore " + to_string(score);
        hasWon = false;
    }

    BigTextBox textBox(text, {0,0});
    textBox.moveTo(centerToScreen(&textBox));
    this_thread::sleep_for(3s);
    textBox.erase();
    startCurrentLevel();
}

string GameManager::getShipDescription(ShipContainer& sc)
{
    return sc.displayName + "\n" + "Top Speed: " + to_string(sc.velocity)
        + "\n Health Points:" + to_string(sc.healthPoints) + "\nFire Rate: "
        + to_string(round(1/((double)sc.fireRate * 0.001))) + "RPS\n" + sc.description;
}

void GameManager::mainMenu()
{
    bool keepPooling = true;
    RenderManager* rm = RenderManager::getInstance();

    int selection = 0;
    BigTextBox title("Space\nInvaders\n \nStart\n \nScoreboard\n \nExit",{170,5});

    Sprite selector("selector");
    selector.moveTo({GW_X - 15,26});

    Sprite spr("xaimite");
    spr.moveTo(Vector2(0, GW_Y/2 - spr.getSize().getY()/2));
    title.draw();

    while (keepPooling)
    {
        short kp = rm->getFirstKeyPressed();
        switch (kp)
        {
            case KEY_UP:
                if (selection == 0)
                {
                    selector.moveBy({0,24});
                    selection = 2;
                }
                else
                {
                    selector.moveBy({0,-12});
                    selection--;
                }
                break;
            case KEY_DOWN:
                if (selection == 2)
                {
                    selector.moveBy({0,-24});
                    selection = 0;
                }
                else
                {
                    selector.moveBy({0,12});
                    selection++;
                }
                break;
            case ' ':
                keepPooling = false;
                break;
            default:
                break;
        }
    }
    switch (selection)
    {
        case 0:
            rm->clearScreen();
            getName();
            rm->clearScreen();
            score = 0;
            shipSelectionMenu();
            playerLives = playerShip->healthPoints;
            startCurrentLevel();
            break;
        case 1:
            scoreBoardMenu();
            break;
        case 2:
            RenderManager::destroyInstance();
            GameClock::destroyInstance();
            AssetManager::destroyInstance();
            exit(0);
            break;
        default:
            break;
    }
}

void GameManager::getName()
{
    RenderManager *rm = RenderManager::getInstance();
    bool keepPooling = true;
    if (!playerName.empty())
        return;

    BigTextBox title("Please insert your name", {0, 0});
    title.moveTo(centerToScreen(&title) + Vector2::Up().multiplyBy(6));
    BigTextBox name = BigTextBox("", {title.getPosition().getX(),(GW_Y/2) - 2});
    BigTextBox desc("Space to Continue", {0,0});
    desc.moveTo({centerToScreen(&desc).getX(),title.getPosition().getY() + 12});

    while (keepPooling)
    {
        short kp = rm->getFirstKeyPressed();
        if (kp == ERR)
            continue;
        switch (kp)
        {
            case ' ':
                if (playerName.empty())
                    break;
                keepPooling = false;
                break;

            case 127:
                playerName = playerName.substr(0, playerName.size() - 1);
                name.erase();
                name = BigTextBox(playerName,{0,0});
                name.moveTo(centerToScreen(&name));
                break;

            default:
                if (playerName.size() >= 14)
                    continue;
                if (!iswalnum(kp))
                    continue;
                stringstream ss;
                ss << (char) kp;
                playerName += ss.str();
                name.erase();
                name = BigTextBox(playerName,{0,0});
                name.moveTo(centerToScreen(&name));
                break;
        }
    }
}

void GameManager::scoreBoardMenu()
{
    RenderManager* rm = RenderManager::getInstance();
    rm->clearInputQueue();
    rm->clearScreen();
    auto scores = AssetManager::getInstance()->getTopScores();
    string bf;
    for (auto& sc : scores)
        bf += sc.playerName + " " + to_string(sc.score) + "\n";
    BigTextBox textBox(bf,{0,0});
    textBox.moveTo(centerToScreen(&textBox) + Vector2(0,3));
    while(true)
    {
        if (rm->getFirstKeyPressed() == ' ')
            break;
    }
    rm->clearScreen();
    mainMenu();

}

