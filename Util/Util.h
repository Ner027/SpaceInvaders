#ifndef SPACEINVADERS_UTIL_H
#define SPACEINVADERS_UTIL_H
#include <vector>
#include <string>

using namespace std;
vector<string> string_split(string str,char ch);
short stos(const std::string& str);

template <typename T>
T clamp(T t,T tMin,T tMax);

#endif
