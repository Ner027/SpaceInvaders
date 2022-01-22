#include "Util.h"
#include "Constants.h"
#include <stdexcept>
#include <random>
#include <locale>

/// Separa uma string no caracter delimitador
/// \param str String a separar
/// \param ch Caracter delimitador
/// \return Lista das strings resultantes da separação
vector<string> string_split(string str,char ch)
{
    vector<string> temp;
    size_t loc;
    //Enquanto não chegar ao fim da string
    while ((loc = str.find(ch)) != string::npos)
    {
        //Adicionar a lista a sub string que vai desde o início da mesma até ao caracter encontradio
        temp.push_back(str.substr(0,loc));
        //A string passa a ser apenas do caracter encontrado para a frente
        str = str.substr(loc + 1,str.length());
    }
    //Inserir na lista o restante
    temp.push_back(str);
    return temp;
}

/// Converte uma string para short
/// \param str String a converter
/// \return short convertido a partir da string
short stos(const std::string& str)
{
    //Primeiro converter para int
    int i = std::stoi(str);

    //Se estiver fora dos limites do short, lançar uma excepção
    if (i > std::numeric_limits<short>::max() || i < std::numeric_limits<short>::min())
        throw std::out_of_range("Fora do limite do tipo short!");

    //Caso contrário retornar
    return (short) i;
}

/// Gera um numero inteiro pseudo aleatório
/// \param lowB Limite inferior
/// \param highB Limite superior
/// \return Numero inteiro entre os limites passados
int randomInt(int lowB, int highB)
{
    /*Dado que o sistema de números aleatórios padrão do C/C++(srand) é bastante previsível
     * usado o metodo "Mersenne Twister" visto que é bastante superior*/
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(lowB,highB);
    return distribution(gen);
}

/// Converter uma string para boolean
/// \param str String a converter
/// \return Valor lógico associado a string
bool stob(const string &str)
{
    //Converter a string para lower case
    string lower = string_toLower(str);
    //retornar conforme o valor
    if (lower == "true")
        return true;
    else if(lower == "false")
        return false;
    //Caso não seja nenhum dos valores válidos lança uma excepção
    else throw invalid_argument("Não foi possivel efetuar a conversão");
}

/// Converte uma string para lower case
/// \param str String a converter
/// \return String em lower case
string string_toLower(const string& str)
{
    /*Obeter o "locale" a usar, quando invocado com uma string vazia
     * o construtor do "locale" tenta obter o do sistem*/

    auto loc = std::locale("");
    string temp;

    //Iterar a string
    for (char c : str)
        //Adicionar a string temporária o caracter em lower case
        temp += tolower(c,loc);
    return temp;
}

/// Calcula a posição necessária para centrar um objecto no ecrã
/// \param so Objecto a calcular a posição
/// \return Vector com a posição
Vector2 centerToScreen(ScreenObject *so)
{
    return Vector2(GW_X,GW_Y).divideBy(2) - so->getSize().divideBy(2);
}

