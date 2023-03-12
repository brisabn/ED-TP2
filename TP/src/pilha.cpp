#include <pilha.hpp>

TipoItem::TipoItem()
{
    esq = -1;
    dir = -1;
}
TipoItem::TipoItem(int c)
{
    chave = c;
}
void TipoItem::SetChave(int c)
{
    chave = c;
}
int TipoItem::GetChave()
{
    return chave;
}
void TipoItem::Imprime()
{
    printf("%d ", chave);
}

// Pilha Encadeada

TipoCelula::TipoCelula()
{
    prox = NULL;
}

PilhaEncadeada::PilhaEncadeada() : Pilha()
{
    topo = NULL;
}

PilhaEncadeada::~PilhaEncadeada()
{
    Limpa();
}

void PilhaEncadeada::Empilha(TipoItem item)
{
    TipoCelula *nova;
    nova = new TipoCelula();

    nova->item = item;
    nova->prox = topo;
    topo = nova;
    tamanho++;
};

TipoItem PilhaEncadeada::Desempilha()
{
    TipoItem aux;
    TipoCelula *p;
    erroAssert(tamanho > 0, "A pilha está vazia");
    aux = topo->item;

    p = topo;
    topo = topo->prox;
    delete p;
    tamanho--;
    return aux;
};

void PilhaEncadeada::Limpa()
{
    while (!Vazia())
        Desempilha();
}