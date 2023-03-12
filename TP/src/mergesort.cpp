#include "mergesort.hpp"

Mergesort::Mergesort()
{
}

void Mergesort::merge(Registro arr[], int esq, int dir, int m)
{
    int i, j, k;
    Registro w[dir - esq + 1];
    i = esq;
    k = 0;
    j = m + 1;

    // faz o merge das duas partes no vetor secundário
    while (i <= m && j <= dir)
    {
        if (arr[i].chave < arr[j].chave)
        {
            // se para o da esquerda for menor, coloca ele no vetor original
            this->comp++;
            this->copias++;
            w[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            // se para o da direita for menor, coloca ele no vetor original
            this->comp++;
            this->copias++;
            w[k] = arr[j];
            k++;
            j++;
        }
    }

    // associa os valores da esquerda ao vetor secundário
    while (i <= m)
    {
        this->copias++;
        w[k] = arr[i];
        k++;
        i++;
    }

    // associa os valores da direita ao vetor secundário
    while (j <= dir)
    {
        this->copias++;
        w[k] = arr[j];
        k++;
        j++;
    }

    // associa o vetor ordenado secundário ao vetor principal
    for (i = esq; i <= dir; i++)
    {
        this->copias++;
        arr[i] = w[i - esq];
    }
}

// A function to split array into two parts.
void Mergesort::mergesort(Registro arr[], int esq, int dir)
{
    int m;
    if (esq < dir)
    {
        m = (esq + dir) / 2;
        // divide a parte da direita e da esqueda
        mergesort(arr, esq, m);
        mergesort(arr, m + 1, dir);

        // faz o merge das duas partes ordenadas
        merge(arr, esq, dir, m);
    }
}