#include "quicksort.hpp"
#include <chrono>
#include <thread>

Quicksort::Quicksort()
{
}

void Quicksort::Selecao(Registro arr[], int esq, int dir)
{
    int i, j, min;
    Registro w;
    for (i = esq; i < dir; i++)
    {
        min = i;
        for (j = i + 1; j < dir + 1; j++)
        {
            // se o elemento atual é menor que o mínimo, o íncice do mínimo torna-se ele
            if (arr[j].chave < arr[min].chave)
            {
                this->comp++;
                min = j;
            }
        }

        // troca entre os elementos
        this->copias++;
        w = arr[i];
        arr[i] = arr[min];
        arr[min] = w;
    }
}

int Quicksort::mediana(Registro arr[], int esq, int dir, int k)
{
    int m, pos;
    Registro med[k];

    // associa ao vetor secundário k valores aleatórios do vetor original
    for (int i = 0; i < k; i++)
    {
        pos = esq + (rand() % (dir - esq + 1)); // a posição é aleatória dentro da faixa selecionada
        med[i] = arr[pos];
    }

    // ordena-se o vetor
    Selecao(med, 0, k - 1);

    // a mediana será o elemento do meio, caso ímpar, e o elemento de k+1/2, caso par
    if (k % 2 != 0)
    {
        m = med[k / 2].chave;
    }
    else
    {
        k++;
        m = med[k / 2].chave;
    }

    return m;
}

void Quicksort::Particao_mediana(int esq, int dir, int *i, int *j, Registro arr[], int k)
{
    int x;
    Registro w;
    *i = esq;
    *j = dir;

    // o pivô é a mediana entre k elementos aleatórios do vetor
    x = mediana(arr, esq, dir, k);

    do
    {
        while (x > arr[*i].chave)
        {
            // compara se o pivo é maior do que o elemento atual, se sim, percorre para direita
            this->comp++;
            (*i)++;
        }
        while (x < arr[*j].chave)
        {
            // compara se o pivo é menor do que o elemento atual, se sim, percorre para esquerda
            this->comp++;
            (*j)--;
        }
        if (*i <= *j)
        {
            // se cruza, realiza uma troca entre os elementos atuais
            w = arr[*i];
            arr[*i] = arr[*j];
            arr[*j] = w;
            this->copias++;

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Quicksort::Particao(int esq, int dir, int *i, int *j, Registro arr[])
{
    int x;
    Registro w;
    *i = esq;
    *j = dir;

    // o pivô é a mediana entre k elementos aleatórios do vetor
    x = arr[(*i + *j) / 2].chave;

    do
    {
        while (x > arr[*i].chave)
        {
            // compara se o pivo é maior do que o elemento atual, se sim, percorre para direita
            this->comp++;
            (*i)++;
        }
        while (x < arr[*j].chave)
        {
            // compara se o pivo é menor do que o elemento atual, se sim, percorre para esquerda
            this->comp++;
            (*j)--;
        }
        if (*i <= *j)
        {
            // se cruza, realiza uma troca entre os elementos atuais
            w = arr[*i];
            arr[*i] = arr[*j];
            arr[*j] = w;
            this->copias++;

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// Versão 1 - Recursivo //
void Quicksort::quickSort_1(Registro arr[], int esq, int dir)
{
    erroAssert(esq >= 0 && dir >= 0, "Intervalo não é válido");
    int i, j;

    Particao(esq, dir, &i, &j, arr);
    if (esq < j)
        quickSort_1(arr, esq, j);
    if (i < dir)
        quickSort_1(arr, i, dir);
}

// Versão 2 - Mediana //
void Quicksort::quickSort_2(Registro arr[], int esq, int dir, int k)
{
    erroAssert(esq >= 0 && dir >= 0, "Faixa não é válido");
    erroAssert(k > 0, "Número de elementos do vetor secundário para não definido");

    int i, j;

    Particao_mediana(esq, dir, &i, &j, arr, k);
    if (esq < j)
        quickSort_2(arr, esq, j, k);
    if (i < dir)
        quickSort_2(arr, i, dir, k);
}

// Versão 3 - Seleção //
void Quicksort::quickSort_3(Registro arr[], int esq, int dir, int m)
{
    erroAssert(esq >= 0 && dir >= 0, "Faixa não é válido");
    erroAssert(m > 0, "Tamanho da seleção não definida");

    int i, j;

    Particao(esq, dir, &i, &j, arr);

    if (dir - esq + 1 <= m) // caso o tamanho do intervalo seja menor ou igual à m, realiza ordenação por seleção
        Selecao(arr, esq, dir);
    else // caso contrário, realiza o quicksort normalmente
    {
        if (esq < j)
        {
            quickSort_3(arr, esq, j, m);
        }
        if (i < dir)
        {
            quickSort_3(arr, i, dir, m);
        }
    }
}

// Versão 4 - Não Recursivo //
void Quicksort::quickSort_4(Registro arr[], int esq, int dir)
{
    erroAssert(esq >= 0 && dir >= 0, "Faixa não é válido");

    PilhaEncadeada pilha;
    TipoItem item;
    int i, j;

    item.dir = dir;
    item.esq = esq;

    pilha.Empilha(item);
    erroAssert(pilha.topo != NULL, "Empilhamento falhou");

    do
    {
        esq = pilha.topo->item.esq;
        dir = pilha.topo->item.dir;

        if (dir > esq)
        {
            Particao(esq, dir, &i, &j, arr);
            pilha.Desempilha(); // desempilha a partição ordenada

            if ((j - esq) < (dir - i)) // se o lado maior é o direito, empilha ele depois
            {
                item.dir = j;
                item.esq = esq;
                pilha.Empilha(item); // empilha o intervalo esquedo (menor) primeiro

                item.esq = i;
                item.dir = dir;
                pilha.Empilha(item);
            }
            else
            {
                item.esq = i;
                item.dir = dir;
                pilha.Empilha(item);

                item.dir = j;
                item.esq = esq;
                pilha.Empilha(item);
            }
        }
        else
        {
            pilha.Desempilha(); // se cruza, desempilha
        }
    } while (!pilha.Vazia());

    pilha.Limpa();
}

// Versão 5 - Empilha Inteligente //
void Quicksort::quickSort_5(Registro arr[], int esq, int dir)
{
    erroAssert(esq >= 0 && dir >= 0, "Faixa não é válido");

    PilhaEncadeada pilha;
    TipoItem item;
    int i, j;

    item.dir = dir;
    item.esq = esq;

    pilha.Empilha(item);
    erroAssert(pilha.topo != NULL, "Empilhamento falhou");

    do
    {
        esq = pilha.topo->item.esq;
        dir = pilha.topo->item.dir;
        if (dir > esq)
        {
            Particao(esq, dir, &i, &j, arr);
            pilha.Desempilha(); // desempilha a partição ordenada

            if ((j - esq) < (dir - i)) // se o lado maior é o direito, empilha ele primeiro
            {
                item.esq = i;
                item.dir = dir;
                pilha.Empilha(item); // empilha o intervalo direito (maior) primeiro

                item.dir = j;
                item.esq = esq;
                pilha.Empilha(item);
                // como o intervalo esquerdo (menor) foi empilhado em cima do intervalo direito (maior),
                // ele será usado primeiro, já que Last In, First Out
            }
            else
            {
                item.dir = j;
                item.esq = esq;
                pilha.Empilha(item);

                item.esq = i;
                item.dir = dir;
                pilha.Empilha(item);
            }
        }
        else
        {
            pilha.Desempilha(); // se cruza, desempilha
        }
    } while (!pilha.Vazia());

    pilha.Limpa();
}
