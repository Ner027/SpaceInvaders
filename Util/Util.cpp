#include "Util.h"
#include <stdexcept>
#include <random>

vector<string> string_split(string str,char ch)
{
    vector<string> temp;
    size_t loc;
    while ((loc = str.find(ch)) != string::npos)
    {
        temp.push_back(str.substr(0,loc));
        str = str.substr(loc + 1,str.length());
    }
    temp.push_back(str);
    return temp;
}


short stos(const std::string& str)
{
    int i = std::stoi(str);

    if (i > std::numeric_limits<short>::max() || i < std::numeric_limits<short>::min())
        throw std::out_of_range("Fora do limite do tipo short!");

    return (short) i;
}


template <typename T>
T clamp(T t,T tMin, T tMax)
{
    if (t < tMin)
        return tMin;
    if (t > tMin)
        return tMax;
    return t;
}

int randomInt(int lowB, int highB)
{
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(lowB,highB);
    return distribution(gen);
}

