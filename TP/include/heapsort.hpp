#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "msgassert.hpp"
#include "registro.hpp"

using namespace std;

class Heapsort
{
public:
    Heapsort();
    int comp = 0;
    int copias = 0;

    void heapsort(Registro arr[], int n);
    void constroi_heap(Registro arr[], int n, int i);
};

#endif