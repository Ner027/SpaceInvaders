#include "GameObject.h"
#include "../Components/Physics.h"
#include "../Managers/GameClock.h"
#include "../Components/Enemy.h"
#include "../Components/EnemyAI.h"
#include "../Components/ICollisionTester.h"
#include "../Components/BetterBoxCollider.h"


void GameObject::tick(char curTick)
{
    //A cada game tick executar todos os componentes que o objecto contem
    for (auto& pair : objectComponents)
        pair.second->execute(curTick);
}

//Metodo que serve para criar um objecto
GameObject *GameObject::Instantiate()
{
    return new GameObject();
}

//O construtor é privado para evitar a criação de objectos sem ser recorrendo a "GameObject::Instantiate"
GameObject::GameObject()
{
    GameClock::getInstance()->registerObject(this);
}


void GameObject::addComponent(const SpriteRenderer& sr)
{
    //Verificar se o objecto ainda não tem nenhum componente deste tipo
    if (objectComponents.contains(sr.getName()))
        return;
    //Criar uma cópia do componente
    auto copy = new SpriteRenderer(sr);
    insertComponent(copy);
}

GameObject::~GameObject()
{
    //Iterar todos os componentes presentes no objecto
    for (auto& pair : objectComponents)
    {
        //Executar o metodo de saida de cada componente
        pair.second->exitCleanly();
        //Apagar o componente
        delete pair.second;
    }
    //Remover da lista de objectos registados do jogo
    GameClock::getInstance()->unregisterForCollisions(this);
    //Apagar o objecto de teste de colisões
    delete collisionTester;
}

void GameObject::addComponent(const AnimatedSprite& as)
{
    if (objectComponents.contains(as.getName()))
        return;
    auto compCopy = new AnimatedSprite(as);
    insertComponent(compCopy);
}

/// Metodo que tenta obter um componente de renderização do objecto
/// \return Componente de renderização do objecto,caso não contenha nenhum retorna nulo
MovableComponent *GameObject::getRenderComp()
{
    //Como é um metodo invocado várias vezes, para aumentar a performance é mantido um componente em cache
    if (cachedRenderComp)
        return cachedRenderComp;

    IComponent* temp = nullptr;

    //Tentar obter um dos componentes de renderização
    if (objectComponents.contains("SpriteRenderer"))
        temp = objectComponents["SpriteRenderer"];
    else if(objectComponents.contains("AnimatedSprite"))
        temp = objectComponents["AnimatedSprite"];

    //Se foi possivél obter um deles retornar o mesmo, após um cast para o tipo MovableComponent
    if (temp)
        cachedRenderComp = dynamic_cast<MovableComponent*>(temp);
    //Caso contrário, lançar uma excepção
    else throw runtime_error("Componente de renderização não encontrado, impossivel mover objecto!");

    return cachedRenderComp;
}

void GameObject::addComponent(const Physics& ph)
{
    if (objectComponents.contains(ph.getName()))
        return;
    auto* compCopy = new Physics(ph);
    insertComponent(compCopy);
}

void GameObject::addComponent(const Bullet& bl)
{
    if (objectComponents.contains(bl.getName()))
        return;

    auto compCopy = new Bullet(bl);
    //Componentes que suportam colisões são tambem atribuidos ao componente de colisão
    colliderComponent = compCopy;
    insertComponent(compCopy);

}

/// Metodo que testa se este objecto está a colidir com outro
/// \param go Objecto a testar a colisão com
/// \return Valor lógico referente a colisão entre objectos
bool GameObject::isColliding(GameObject *go)
{
    //Caso este objecto não tem um testador de colisões então não irá colidir
    if (!collisionTester)
        return false;
    //Caso contrário, retornar o valor obtido pelo mesmo
    return collisionTester->testCollision(this,go);
}

//Wrapper functions para facilitar o uso do objecto

Vector2 GameObject::getPosition()
{
    return getRenderComp()->getPosition();
}

 Vector2 GameObject::getSize()
{
    return getRenderComp()->getSize();
}

void GameObject::moveBy(const Vector2 & df)
{
    getRenderComp()->moveBy(df);
}

void GameObject::moveTo(const Vector2 &nPos)
{
    getRenderComp()->moveTo(nPos);
}


void GameObject::addComponent(const Enemy &en)
{
    if (objectComponents.contains(en.getName()))
        return;
    auto compCopy = new Enemy(en);
    colliderComponent = compCopy;
    insertComponent(compCopy);
}

///
/// \param compName Nome do componente a procurar
/// \return Componente caso tenha sido encontrado,ou nulo
IComponent* GameObject::getComponent(const string& compName)
{
    if (objectComponents.contains(compName))
        return objectComponents[compName];

    return nullptr;
}

void GameObject::addComponent(const EnemyAI &en)
{
    if (objectComponents.contains(en.getName()))
        return;
    insertComponent(new EnemyAI(en));
}

void GameObject::insertComponent(IComponent* ic)
{
    objectComponents.insert(pair<string,IComponent*>(ic->getName(),ic));
    ic->onAdd();
}

long GameObject::getId() const
{
    return selfId;
}

/// Define o tipo de testador de colisões que este objecto irá usar
/// \param tester
void GameObject::setCollisionTester(CollisionTester tester)
{
    //Cria um testador
    if (tester == BETTER_BOUNDING_BOX)
        collisionTester = new BetterBoxCollider();
    //Regista o objecto para colisões
    GameClock::getInstance()->registerForCollisions(this);
}

/// Metodo que tenta definir a velocidade do objecto,caso este não tenha um componente de fisicas,lança uma excepção
/// \param x Velocidade em X
/// \param y Velocidade em Y
/// \param multiplier Multiplicador da velocidade
void GameObject::setVelocity(float x, float y,int multiplier = 1)
{
    auto comp = getComponent("Physics");
    if (comp == nullptr)
        throw runtime_error("O objecto não tem um componente de fisicas");
    auto pComp = dynamic_cast<Physics*>(comp);
    pComp->setVelocity(x,y,multiplier);
}



