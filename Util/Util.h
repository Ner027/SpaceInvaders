#ifndef SPACEINVADERS_UTIL_H
#define SPACEINVADERS_UTIL_H
#include <vector>
#include <string>
#include "../Data/Vector2.h"
#include "../CursesWrapper/ScreenObject.h"

using namespace std;
vector<string> string_split(string str,char ch);
short stos(const string& str);
int randomInt(int lowB,int highB);
string string_toLower(const string& string);
bool stob(const string& str);
Vector2 centerToScreen(ScreenObject* so);


#endif
