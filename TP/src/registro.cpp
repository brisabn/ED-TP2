#include "registro.hpp"

Registro::Registro()
{
    gerar_numbers();
    gerar_strings();
}

void Registro::gerar_numbers()
{
    // Para testar diferença de tempo na criação de números aleatórios
    // foi implementado um gerador de números aleatórios
    for (int i = 0; i < 10; i++)
    {
        numbers[i] = 1; // rand() % 1000
    }
}

void Registro::gerar_strings()
{

    std::string str;
    str.resize(200);

    for (int i = 0; i < 200; i++)
        str[i] = 'a';

    for (int j = 0; j < 15; j++)
    {
        palavras[j] = str;
    }

    /*
    // Para testar diferença de tempo na criação de strings aleatórias
    // foi implementado um gerador de cadeias aleatórias
    static const char letras[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 200; i++)
            str[i] = letras[rand() % (sizeof(letras) - 1)];

        palavras[j] = str;
    }
    */
}
