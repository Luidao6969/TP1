
#include <iostream>
#include "../include/Sort.hpp"

Sort::Sort() {}

Sort::~Sort() {}

void Sort::swap(int *a, int *b, Estatistica *est)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    est->trocas += 3; // 3 movimentações 
}

void Sort::insertionSort(int *V, int ini, int fim, Estatistica *est)
{
    est->chamadas++;
    for (int i = ini + 1; i <= fim; i++)
    {
        int chave = V[i];
        est->trocas++;
        int j = i - 1;

        while ((est->comparacoes++, V[j] > chave) && j >= ini)
        {
            V[j + 1] = V[j];
            est->trocas++;
            j--;
        }
        V[j + 1] = chave;
        est->trocas++;
    }
}

int Sort::median(int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}


void Sort::partition3(int *A, int l, int r, int *i, int *j, Estatistica *est) {
    est->chamadas++;
    *i = l;
    *j = r;

    int pivo = median(A[l], A[(l + r) / 2], A[r]);

    do {
        while (A[*i] < pivo) {
            (*i)++;
            est->comparacoes++;
        }
        est->comparacoes++;

        while (A[*j] > pivo) {
            (*j)--;
            est->comparacoes++;
        }
        est->comparacoes++;

        if (*i <= *j) {
            swap(&A[*i], &A[*j], est);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Sort::quickSortIns(int *V, int ini, int fim, Estatistica *est, int limiar)
{
    est->chamadas++;

    int i, j;
    partition3(V, ini, fim, &i, &j, est); // usa medianaDeTres internamente

    if (ini < j) {
        if (j - ini < limiar)
            insertionSort(V, ini, j, est);
        else
            quickSortIns(V, ini, j, est, limiar);
    }

    if (i < fim) {
        if (fim - i < limiar)
            insertionSort(V, i, fim, est);
        else
            quickSortIns(V, i, fim, est, limiar);
    }
}

