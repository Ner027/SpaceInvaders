#include "Util.h"
#include "Constants.h"
#include <stdexcept>
#include <random>
#include <locale>

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

int randomInt(int lowB, int highB)
{
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(lowB,highB);
    return distribution(gen);
}

bool stob(const string &str)
{
    string lower = string_toLower(str);
    if (lower == "true")
        return true;
    else if(lower == "false")
        return false;
    else throw invalid_argument("Não foi possivel efetuar a conversão");
}

string string_toLower(const string& str)
{
    auto loc = std::locale("");
    string temp;
    for (char c : str)
        temp += tolower(c,loc);
    return temp;
}

Vector2 centerToScreen(ScreenObject *so)
{
    return Vector2(GW_X,GW_Y).divideBy(2) - so->getSize().divideBy(2);
}

