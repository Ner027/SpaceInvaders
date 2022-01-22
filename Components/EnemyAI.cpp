#include <cmath>
#include "EnemyAI.h"
#include "../Util/Constants.h"
#include "Enemy.h"
#include "Physics.h"
#include "../Util/Util.h"
#include "../Managers/AssetManager.h"

void EnemyAI::execute(char curTick)
{
    //Se todos os inimigos já tiverem morrido, fazer com que o jogador ganhe o jogo
    if (enemyCount == enemiesKilled)
        gameManager->winCurrentLevel();

    Vector2 farRight = Vector2::Zero();
    Vector2 farLeft = Vector2::Right().multiplyBy(GW_X);

    //Iterar os inimigos
    for (auto it = enemies.cbegin();it != enemies.end();)
    {
        auto go = (*it).enemy;
        auto gridPosition = (*it).position;

        //Se o inimigo tiver sido atingido
        if (go->markedForDelete)
        {
            enemiesKilled++;//Aumentar a kill count
            enemies.erase(it);//Remover da lista de inimigos
            isFree[gridPosition.getX() + (gridPosition.getY() * 9)] = true;//Colocar o lugar na grid de inimigos como livre
        }
        else ++it;

        //Mover o inimigo
        go->moveBy(currentVelocity);

        //Obter os extermos das filas de inimigos
        auto position = go->getPosition();
        if (position.getX() >= farRight.getX())
            farRight = position + go->getSize();
        if(position.getX() <= farLeft.getX())
            farLeft = position;

        //Se o inimigo pode disparar
        if (canShoot(gridPosition))
        {
            //Disparar uma bala
            Vector2 spawnPos(go->getPosition() + Vector2(go->getSize().getX() / 2,go->getSize().getY() + 1));
            spawnBullet(spawnPos,go);
            lastEnemy = gridPosition;
        }
    }

    //TODO:Melhorar isto multipliers tao todos cegos

    int speedMultiplier = 1;
    if (enemiesKilled > enemyCount * 0.25)
    {
        if (enemiesKilled < enemyCount * 0.75)
            speedMultiplier = 2;
        else speedMultiplier = 3;
    }

    //Se o extermo direito estiver no fim da janela do jogo
    if (farRight.getX() >= GW_X)
    {
        //Mover todos os inimigos 1 para baixo
        for (const auto& go : enemies)
            go.enemy->moveBy(Vector2::Down());
        //Mudar a direção dos inimigos para a esquerda
        currentVelocity = Vector2::Left().multiplyBy(speedMultiplier);
    }
    //Semelhante ao anterior, apenas para o lado esquerdo
    else if (farLeft.getX() <= 0)
    {
        for (const auto& go : enemies)
            go.enemy->moveBy(Vector2::Down());
        currentVelocity = Vector2::Right().multiplyBy(speedMultiplier);
    }
}

void EnemyAI::exitCleanly()
{
    //Quando a AI for eliminada apagar todos os inimigos associados á mesma
    for (auto& go : enemies)
        go.enemy->markedForDelete = true;
}

EnemyAI::EnemyAI(const vector<string>& enemyNames) : currentVelocity(Vector2::Right())
{
    this->enemyNames = enemyNames;
    gameManager = GameManager::getInstance();
}

void EnemyAI::onAdd()
{
    rows = (int) enemyNames.size();

    AssetManager* am = AssetManager::getInstance();
    Vector2 basePosition = Vector2::Zero();

    for (int i = 0; i < rows; ++i)
    {
        //Cada fila tem um Sprite diferente
        AnimatedSprite enemySpriteRenderer(enemyNames[i]);
        for (int j = 0; j < 9; ++j)
        {
            //Calcular posição dos elementos
            Vector2 newPosition = Vector2(enemySpriteRenderer.getSize().getX() + 3,0).multiplyBy(j) + basePosition;
            //Criar o inimigo e os seus componentes
            auto enemy = GameObject::Instantiate();
            enemy->addComponent(enemySpriteRenderer);
            enemy->moveTo(newPosition);
            Enemy en(am->getEnemyScore(enemyNames[i]));
            enemy->addComponent(en);
            //Habilitar as colisões para o objeto, com o tipo BETTER_BOUNDING_BOX
            enemy->setCollisionTester(BETTER_BOUNDING_BOX);
            enemies.push_back(EnemyContainer(enemy,{j,i}));
        }
        basePosition += Vector2::Down().multiplyBy(enemySpriteRenderer.getSize().getY()) + Vector2::Down().multiplyBy(2);
    }
    enemyCount = (int) enemies.size();
}

bool EnemyAI::canShoot(const Vector2& position)
{
    //Se ainda não pode disparar retornar falso
    if (!gameManager->enemyCanFire)
        return false;

    //Para evitar que o mesmo inimigo dispare 2 vezes seguidas
    if (position == lastEnemy && enemies.size() != 1)
        return false;

    //Chance de disparar
    int ri = randomInt(0,100);
    //O valor a direita é a percentagem de chance
    if (ri > 10)
        return false;

    /*Verificar se todas as posições abaixo do inimigo que irá disparar
     * estão livres*/

    for (int i = position.getY() + 1; i < rows; ++i)
    {
        //Se alguma não estiver livre retornar falso
        if (!isFree[position.getX() + (i * 9) ])
            return false;
    }

    //Caso todas as verifições passem retornar true
    return true;
}

void EnemyAI::spawnBullet(const Vector2 &position,GameObject* parent)
{
    auto bulletObject = GameObject::Instantiate();
    SpriteRenderer spriteRenderer("bullet_enemy");
    bulletObject->addComponent(spriteRenderer);
    bulletObject->moveTo(position);
    Physics bulletPhysics(bulletObject,0,BULLET_SPEED);
    bulletObject->addComponent(bulletPhysics);
    Bullet bullet(parent);
    bulletObject->addComponent(bullet);
    bulletObject->setCollisionTester(BETTER_BOUNDING_BOX);
    gameManager->enemyCanFire = false;
}
