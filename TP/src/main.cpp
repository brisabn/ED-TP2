#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <quicksort.hpp>
#include <mergesort.hpp>
#include <heapsort.hpp>

#include <registro.hpp>

using namespace std;

// variáveis globais
bool entrada, saida;
bool recursivo, mediana, selecao, nao_recursivo, empilha;
bool heapsort, mergesort, quicksort;

string arquivo_entrada;
string arquivo_saida;
int elem_mediana, tam_selecao, semente;

void parse_args(int argc, char const *argv[])
{
    for (int i = 0; i < argc; i++)
    {

        // seleção do algoritmo de ordenação
        if (string(argv[i]) == "heapsort")
        {
            heapsort = true;
        }

        if (string(argv[i]) == "mergesort")
        {
            mergesort = true;
        }

        if (string(argv[i]) == "quicksort")
        {
            quicksort = true;
        }

        // arquivos de entrada e saída
        if (string(argv[i]) == "-i")
        {
            entrada = true;
            arquivo_entrada = argv[i + 1];
        }

        if (string(argv[i]) == "-o")
        {
            saida = true;
            arquivo_saida = argv[i + 1];
        }

        // semente
        if (string(argv[i]) == "-s")
        {
            erroAssert(atoi(argv[i + 1]) > 0, "Semente inválida");
            semente = atoi(argv[i + 1]);
        }

        if (quicksort)
        {

            // seleção da versão do quicksort
            if (string(argv[i]) == "-v")
            {
                switch (atoi(argv[i + 1]))
                {
                case 1:
                    recursivo = true;
                    break;
                case 2:
                    mediana = true;
                    break;
                case 3:
                    selecao = true;
                    break;
                case 4:
                    nao_recursivo = true;
                    break;
                case 5:
                    empilha = true;
                    break;
                }
                erroAssert(atoi(argv[i + 1]) >= 1 && atoi(argv[i + 1]) <= 5, "Número inválido de versão do quicksort");
            }

            // parâmetros
            if (string(argv[i]) == "-k")
            {
                erroAssert(atoi(argv[i + 1]) > 0, "Parâmetro k inválido");
                elem_mediana = atoi(argv[i + 1]);
            }
            if (string(argv[i]) == "-m")
            {
                erroAssert(atoi(argv[i + 1]) > 0, "Parâmetro m inválido");
                tam_selecao = atoi(argv[i + 1]);
            }
        }
    }
}

void randomico(int n, Registro arr[])
{
    for (int j = 0; j < n; j++)
        for (int i = 0; i < 5; i++)
        {
            ((arr + i * n)[j]).chave = rand();
        }
}

void conj_n(Registro arr[], Registro col[], int i, int n)
{
    // o conjunto é um vetor coluna da matriz
    for (int j = 0; j < n; j++)
    {
        col[j] = ((arr + i * n)[j]);
    }
}

int main(int argc, char const *argv[])
{
    parse_args(argc, argv);
    erroAssert(quicksort || heapsort || mergesort, "Método de ordenação não selecionado");

    Quicksort q;
    Mergesort m;
    Heapsort h;

    ifstream myfile;
    ofstream output;

    string line;
    int qnt_n;

    myfile.open(arquivo_entrada);
    erroAssert(myfile, "Erro na abertura do arquivo");

    getline(myfile, line);
    erroAssert(line[0], "Arquivo vazio");
    qnt_n = stoi(line);

    // identifica a quantidade de N
    int qnt = 0, i = 0;
    int tamanho[qnt_n];
    while (getline(myfile, line))
    {
        tamanho[qnt] = stoi(line);
        qnt++;
    }

    output.open(arquivo_saida);
    erroAssert(output, "Erro na abertura do arquivo");

    // declaração de vetores da cada estatística de cada conjunto
    int est_comp[5];
    int est_copias[5];
    float est_tempo[5];

    srand(semente);
    while (i < qnt_n)
    {
        float tempo = 0;
        int conj = 0;
        int n = tamanho[i];
        int media_compara = 0, media_copias = 0;
        float media_tempo = 0;

        Registro *arr = new Registro[n * 5];
        Registro *col = new Registro[n];

        randomico(n, arr);

        output << "N: " << n << endl;

        while (conj < 5)
        {
            int n = tamanho[i];

            /*
            // gerador de vetores aleatórios para cada conjunto - utilizado na análise da parte 2.2 do trabalho
            srand(rand() % 100000);
            for (int i = 0; i < n; i++)
            {
                col[i].chave = rand();
            }*/

            conj_n(arr, col, conj, n);

            if (recursivo)
            {
                q.comp = 0;
                q.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                q.quickSort_1(col, 0, n - 1);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = q.comp;
                est_copias[conj] = q.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += q.comp;
                media_copias += q.copias;
            }
            if (mediana)
            {
                q.comp = 0;
                q.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                q.quickSort_2(col, 0, n - 1, elem_mediana);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = q.comp;
                est_copias[conj] = q.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += q.comp;
                media_copias += q.copias;
            }
            if (selecao)
            {
                q.comp = 0;
                q.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                q.quickSort_3(col, 0, n - 1, tam_selecao);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = q.comp;
                est_copias[conj] = q.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += q.comp;
                media_copias += q.copias;
            }
            if (nao_recursivo)
            {
                q.comp = 0;
                q.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                q.quickSort_4(col, 0, n - 1);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = q.comp;
                est_copias[conj] = q.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += q.comp;
                media_copias += q.copias;
            }
            if (empilha)
            {
                q.comp = 0;
                q.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                q.quickSort_5(col, 0, n - 1);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = q.comp;
                est_copias[conj] = q.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += q.comp;
                media_copias += q.copias;
            }

            if (heapsort)
            {
                h.comp = 0;
                h.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                h.heapsort(col, n);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = h.comp;
                est_copias[conj] = h.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += h.comp;
                media_copias += h.copias;
            }
            if (mergesort)
            {
                m.comp = 0;
                m.copias = 0;
                auto start = std::chrono::high_resolution_clock::now();

                m.mergesort(col, 0, n - 1);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = end - start;

                tempo = float_ms.count();

                est_comp[conj] = m.comp;
                est_copias[conj] = m.copias;
                est_tempo[conj] = tempo;

                media_tempo += tempo;
                media_compara += m.comp;
                media_copias += m.copias;
            }
            conj++;
        }

        // impressão das métricas no arquivo de saída
        output << "----- Número de Comparações -----" << endl;
        for (int c = 0; c < 5; c++)
        {
            output << est_comp[c] << "   ";
        }
        output << "\nMédia = " << media_compara / 5 << endl;

        output << "----- Número de Cópias -----" << endl;
        for (int c = 0; c < 5; c++)
        {
            output << est_copias[c] << "   ";
        }
        output << "\nMédia = " << media_copias / 5 << endl;

        output << "----- Tempo de execução -----" << endl;
        for (int c = 0; c < 5; c++)
        {
            output << est_tempo[c] << "   ";
        }
        output << "\nMédia = " << media_tempo / 5.0 << endl;

        output << endl;

        i++;
        delete[] col;
        delete[] arr;
    }

    myfile.close();
    erroAssert(!myfile, "Erro no fechamento do arquivo");

    output.close();

    return 0;
}