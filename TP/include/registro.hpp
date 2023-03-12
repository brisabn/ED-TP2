#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "msgassert.hpp"
#include "registro.hpp"

using namespace std;

class Registro
{
public:
    Registro();
    int chave;
    string palavras[15];
    float numbers[10];

    void gerar_strings();
    void gerar_numbers();
};

#endif