#ifndef SPACEINVADERS_SCORECONTAINER_H
#define SPACEINVADERS_SCORECONTAINER_H
#include <string>

using namespace std;
struct ScoreContainer{
    int score;
    string playerName;

    friend bool operator<(const ScoreContainer& left, const ScoreContainer& right)
    {
        return left.score<right.score;
    }
    ScoreContainer() {score = 0;playerName = "";}
    ScoreContainer(int score,const string& playerName)
    {
        this->score=score;
        this->playerName=playerName;
    };
};
#endif
