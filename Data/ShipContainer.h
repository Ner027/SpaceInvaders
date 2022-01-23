#ifndef SPACEINVADERS_SHIPCONTAINER_H
#define SPACEINVADERS_SHIPCONTAINER_H
#include <string>

using namespace std;
struct ShipContainer
{
public:
    string spriteName;
    string displayName;
    float velocity;
    long fireRate;
    short healthPoints;
    string description;
    ShipContainer(const string& sprName,const string& displayName, const string& desc,float vel,long fRate,short hp)
    {
        this->displayName = displayName;
        this->spriteName = sprName;
        this->velocity = vel;
        this->description = desc;
        this->fireRate = fRate;
        this->healthPoints = hp;
    }
};

#endif
