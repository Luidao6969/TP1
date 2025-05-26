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
    Ordenador(double coefA, double coefB, double coefC); // Construtor dos coeficientes de custo
    ~Ordenador();
    Estatistica ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras);
    int determinaLimiarParticao(int *V, int tam, int limiarCusto); 
    void calculaNovaFaixa(int limParticao, int *minMPS, int *maxMPS, int *passoMPS, int numMPS, Estatistica *custo); //  Calcula uma nova faixa de valores de minParticao
    int shuffleVector(int *vet, int size, int numShuffle); // Embaralha aleatoriamente o vetor
    int menorCusto(Estatistica *custo, int numMPS); // Determina índice do menor custo
    int getMPS(int i, Estatistica *custo); // Acessa o valor de minParticao em uma posição do vetor de custos.
    void imprimeEstatisticas(Estatistica e);
    int contarQuebras(int *V, int tam); // Calcula as quebras de ordem
    int findIndexMPS(int mps, Estatistica *custo, int numMPS); // Retorna o índice de uma estatística no vetor custo
    int determinaLimiarQuebras(int *V, int tam, int limiarCusto, int minTamParticao, int seed);
    
};

#endif