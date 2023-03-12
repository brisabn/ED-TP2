#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <pilha.hpp>

#include <registro.hpp>

using namespace std;

class Quicksort
{
public:
    Quicksort();
    int comp = 0;
    int copias = 0;

    void quickSort_1(Registro arr[], int low, int high);
    void quickSort_2(Registro arr[], int low, int high, int k);
    void quickSort_3(Registro arr[], int low, int high, int m);
    void quickSort_4(Registro arr[], int low, int high);
    void quickSort_5(Registro arr[], int low, int high);

    void Particao_mediana(int esq, int dir, int *i, int *j, Registro A[], int k);
    void Particao(int esq, int dir, int *i, int *j, Registro A[]);
    void Selecao(Registro arr[], int esq, int dir);
    int mediana(Registro arr[], int esq, int dir, int k);
};

#endif