#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>

#include "msgassert.hpp"

#include <registro.hpp>

using namespace std;

class Mergesort
{
public:
    Mergesort();
    int comp = 0;
    int copias = 0;

    void mergesort(Registro arr[], int esq, int dir);
    void merge(Registro arr[], int esq, int dir, int m);
};

#endif