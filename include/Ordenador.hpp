#ifndef ORDENADOR 
#define ORDENADOR

#include <stdlib.h>   // Para drand48, malloc, free
#include <stdio.h>    // Para printf
#include <math.h>     // Para fabs()
#include <iostream>

using namespace std;

#include "../include/Estatisticas.hpp"
#include "../include/Sort.hpp"
class Ordenador
{
private:
    int numeroQuebras; 
    double a; // coeficientes de custo
    double b; // coeficientes de custo
    double c; // coeficientes de custo
public:
    Ordenador(double coefA, double coefB, double coefC);
    ~Ordenador();
    Estatistica ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras);
    int determinaLimiarParticao(int *V, int tam, int limiarCusto);
    void calculaNovaFaixa(int limParticao, int *minMPS, int *maxMPS, int *passoMPS, int numMPS, Estatistica *custo);
    int shuffleVector(int *vet, int size, int numShuffle);
    int menorCusto(Estatistica *custo, int numMPS);
    int getMPS(int i, Estatistica *custo);
    void imprimeEstatisticas(Estatistica e);
    int contarQuebras(int *V, int tam);
    int findIndexByMPS(int mps, Estatistica *custo, int numMPS);
    int determinaLimiarQuebras(int *V, int tam, int limiarCusto, int minTamParticao, int seed);
    
};

#endif