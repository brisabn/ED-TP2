#include "heapsort.hpp"

Heapsort::Heapsort()
{
}

void Heapsort::constroi_heap(Registro arr[], int n, int raiz)
{
    Registro w;
    int maior = raiz; // o maior vai ser a raiz do heap, que tem estrutura de árvore
    int esq = 2 * raiz + 1;
    int dir = 2 * raiz + 2;

    // se a ramificação da esquerda for maior que a root, então o maior é da esquerda
    if (esq < n && arr[esq].chave > arr[maior].chave)
    {
        comp++;
        maior = esq;
    }

    // se a ramificação da direita for maior que a root, então o maior é da direita
    if (dir < n && arr[dir].chave > arr[maior].chave)
    {
        comp++;
        maior = dir;
    }

    if (maior != raiz)
    {
        // se o maior não for a raiz, então faz uma troca da raiz pelo maior
        this->copias++;
        w = arr[raiz];
        arr[raiz] = arr[maior];
        arr[maior] = w;

        // constrói o heap recursivamente para cama ramo
        constroi_heap(arr, n, maior);
    }
}

void Heapsort::heapsort(Registro arr[], int n)
{
    Registro w;

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        // constrói o heap a cada metade
        constroi_heap(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        // a raiz vai para o final por meio de trocas;
        this->copias++;
        w = arr[0];
        arr[0] = arr[i];
        arr[i] = w;

        // constói o heap com a raiz pro final
        constroi_heap(arr, i, 0);
    }
}