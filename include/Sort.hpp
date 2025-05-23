#ifndef SORT
#define SORT

#include "../include/Estatisticas.hpp"
class Sort
{
private:
    
public:
    Sort();
    ~Sort();
    void insertionSort(int *V, int ini, int fim, Estatistica *est);
    int median(int a, int b, int c);
    void partition3(int *A, int l, int r, int *i, int *j, Estatistica *est);
    void quickSortIns(int *V, int ini, int fim, Estatistica *est, int limiar);
    void swap(int *a, int *b, Estatistica *est);
};

#endif
