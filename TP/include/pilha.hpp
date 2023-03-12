#ifndef PILHA_HPP
#define PILHA_HPP

#include <iostream>
#include <sstream>
#include <string>

#include "msgassert.hpp"

using namespace std;

class TipoItem
{
public:
    TipoItem();
    TipoItem(int c);
    void SetChave(int c);
    int GetChave();
    void Imprime();

    int chave;

    int esq, dir;
};

class TipoCelula
{
public:
    TipoCelula();
    TipoItem item;
    TipoCelula *prox;
    friend class PilhaEncadeada;
};

class Pilha
{
public:
    Pilha() { tamanho = 0; };
    int GetTamanho() { return tamanho; };
    bool Vazia() { return tamanho == 0; };
    virtual void Empilha(/*int esq, int dir*/ TipoItem item) = 0;
    virtual TipoItem Desempilha() = 0;
    virtual void Limpa() = 0;

    int tamanho = 0;
};

class PilhaEncadeada : public Pilha
{
public:
    PilhaEncadeada();
    virtual ~PilhaEncadeada();
    void Empilha(/*int esq, int dir*/ TipoItem item);
    TipoItem Desempilha();
    void Limpa();

    TipoCelula *topo;
};

#endif