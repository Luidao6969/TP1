#include "../include/Ordenador.hpp"
#include <cstdlib> // Para drand48()
#include <cmath>   // Para fabs()
#include <cstdio>  // Para printf()

Ordenador::Ordenador(double coefA, double coefB, double coefC)
{
    numeroQuebras = 0;
    a = coefA;
    b = coefB;
    c = coefC;

    if (a <= 0 && b <= 0 && c <= 0)
    {
       cout << "Aviso: todos os coeficientes de custo são zero ou negativos." << endl;
    }
}

Ordenador::~Ordenador() {}

int Ordenador::contarQuebras(int *V, int tam)
{
    int quebras = 0;
    for (int i = 1; i < tam; i++)
    {
        if (V[i] < V[i - 1])
        {
            quebras++;
        }
    }
    return quebras;
}

void Ordenador::imprimeEstatisticas(Estatistica e)
{
    printf("mps %3d cost %.9lf cmp %6d move %5d calls %4d\n",
           e.minParticao, e.custo, e.comparacoes, e.trocas, e.chamadas);
}

int Ordenador::menorCusto(Estatistica *custo, int numMPS)
{
    int idx = 0;
    for (int i = 1; i < numMPS; i++)
    {
        if (custo[i].custo < custo[idx].custo)
        {
            idx = i;
        }
    }
    return idx;
}

int Ordenador::getMPS(int i, Estatistica *custo)
{
    return custo[i].minParticao;
}

void Ordenador::calculaNovaFaixa(int limParticao, int *minMPS, int *maxMPS, int *passoMPS, int numMPS, Estatistica *custo)
{
    int newMin, newMax;

    if (limParticao == 0)
    {
        newMin = 0;
        newMax = 2;
    }
    else if (limParticao == numMPS - 1)
    {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    }
    else
    {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }

    *minMPS = getMPS(newMin, custo);
    *maxMPS = getMPS(newMax, custo);
    *passoMPS = (*maxMPS - *minMPS) / 5;
    if (*passoMPS == 0)
        (*passoMPS) = 1;
}

int Ordenador::findIndexMPS(int mps, Estatistica *custo, int numMPS)
{
    for (int i = 0; i < numMPS; i++)
    {
        if (custo[i].minParticao == mps)
        {
            return i;
        }
    }
    return -1; // Erro, não encontrado
}

int Ordenador::determinaLimiarParticao(int *V, int tam, int limiarCusto)
{
    if (V == nullptr || tam <= 0)
    {
        printf("Erro: vetor nulo ou tamanho inválido.\n");
        return -1;
    }
    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0)
        passoMPS = 1;

    int posMin, posMax;
    Estatistica custo[10];
    int numMPS = 0;
    double diffCusto = INFINITY;
    int limParticao = minMPS;
    int maxIteracoes = 5;
    int contador = 0;

    numeroQuebras = contarQuebras(V, tam); // Numero de quebras do vetor

    while ((diffCusto > limiarCusto) && (maxMPS - minMPS) >= 5 && contador < maxIteracoes) // Executa até que o custo convirja (diffCusto abaixo do limite)
    {
        numMPS = 0;
        printf("iter %d \n", contador++);
        // cout << "maxMPS: " << maxMPS << endl;
        for (int t = minMPS; t <= maxMPS; t += passoMPS)
        {
            int copia[tam]; // Cria uma cópia do vetor original para não alterar os dados entre execuções
            for (int i = 0; i < tam; i++)
                copia[i] = V[i];
            custo[numMPS] = ordenadorUniversal(copia, tam, t, numeroQuebras);
            imprimeEstatisticas(custo[numMPS]);
            numMPS++;
        }

        limParticao = menorCusto(custo, numMPS); // Identifica o índice com menor custo
        calculaNovaFaixa(limParticao, &minMPS, &maxMPS, &passoMPS, numMPS, custo);
        posMin = findIndexMPS(minMPS, custo, numMPS); // Encontra os índices
        posMax = findIndexMPS(maxMPS, custo, numMPS); // Encontra os índices
        if (posMin == -1 || posMax == -1)
        {
            printf("Erro: minMPS ou maxMPS não encontrado nos custos!\n");
            diffCusto = 0;
        }
        else
        {
            diffCusto = fabs(custo[posMin].custo - custo[posMax].custo);
        }
        printf("nummps %d limParticao %d mpsdiff %.6lf\n", numMPS, custo[limParticao].minParticao, diffCusto);
        cout << endl;
    }
    return custo[limParticao].minParticao;
}

Estatistica Ordenador::ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras)
{
    Estatistica e;
    e.comparacoes = 0;
    e.trocas = 0;
    e.chamadas = 0;
    e.minParticao = minTamParticao;

    Sort s;
    int contadorInsertion = 0;
    int contadorQuick = 0;
    if (numeroQuebras < limiarQuebras) // Seleção do algorítmo de ordenação
    {
        s.insertionSort(V, 0, tam - 1, &e);
        contadorInsertion++;
    }
    else
    {
        if (tam > minTamParticao)
        {
            s.quickSortIns(V, 0, tam - 1, &e, minTamParticao);
            contadorQuick++;
        }
        else
        {
            s.insertionSort(V, 0, tam - 1, &e);
            contadorInsertion++;
        }
    }
    e.custo = a * e.comparacoes + b * e.trocas + c * e.chamadas;
    // cout << "Numero de vezes que foi chamado o quicksort:" << contadorQuick;
    // cout << "Numero de vezes que foi chamado o insertionsort:" << contadorInsertion;
    return e;
}

int Ordenador::shuffleVector(int *vet, int size, int numShuffle)
{
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++)
    {
        while (p1 == p2)
        {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }
    return 0;
}

int Ordenador::determinaLimiarQuebras(int *V, int tam, int limiarCusto, int minTamParticao, int seed)
{
    int minLQ = 1;
    int maxLQ = tam / 2;
    int passoLQ = (maxLQ - minLQ) / 5;
    if (passoLQ == 0)
        passoLQ = 1;
        
    if (limiarCusto < 0){
        return -1;
    }

    Sort s2;
    Estatistica e2;
    Estatistica custoQS[10], custoINS[10];
    int lqTestados[10];
    int numLQ = 0;
    double diffCusto = 1e9;
    int limQuebrasIdx = 0;
    int maxIteracoes = 7;
    int contador = 0;

    // Cria vetor ordenado base
    int Vord[tam];
    for (int i = 0; i < tam; i++)
        Vord[i] = V[i];
    s2.insertionSort(Vord, 0, tam - 1, &e2);

    while ((contador < maxIteracoes))
    {
        numLQ = 0;
        printf("iter %d\n", contador++);
        for (int q = minLQ; q <= maxLQ && numLQ < 7; q += passoLQ)
        { // Testa diferentes quantidades de quebras, limitando no máximo 7 por iteração
            lqTestados[numLQ] = q;

            // Cria vetor embaralhado com exatamente q quebras
            int VcopyQS[tam], VcopyINS[tam];
            for (int i = 0; i < tam; i++)
            {
                VcopyQS[i] = Vord[i];
                VcopyINS[i] = Vord[i];
            }
            srand48(seed);
            shuffleVector(VcopyQS, tam, q);
            srand48(seed);
            shuffleVector(VcopyINS, tam, q);

            Estatistica eQS;
            eQS.comparacoes = eQS.trocas = eQS.chamadas = 0;
            eQS.minParticao = minTamParticao;
            Sort sQS;
            sQS.quickSortIns(VcopyQS, 0, tam - 1, &eQS, minTamParticao);
            eQS.custo = a * eQS.comparacoes + b * eQS.trocas + c * eQS.chamadas;
            custoQS[numLQ] = eQS;

            Estatistica eINS;
            eINS.comparacoes = eINS.trocas = eINS.chamadas = 0;
            eINS.minParticao = tam + 1;
            Sort sINS;
            sINS.insertionSort(VcopyINS, 0, tam - 1, &eINS);
            eINS.custo = a * eINS.comparacoes + b * eINS.trocas + c * eINS.chamadas;
            custoINS[numLQ] = eINS;

            printf("qs lq %3d cost %.9lf cmp %6d move %5d calls %4d\n",
                   q, eQS.custo, eQS.comparacoes, eQS.trocas, eQS.chamadas);

            printf("in lq %3d cost %.9lf cmp %6d move %5d calls %4d\n",
                   q, eINS.custo, eINS.comparacoes, eINS.trocas, eINS.chamadas);

            numLQ++;
        }

        double menorDif = fabs(custoQS[0].custo - custoINS[0].custo); // Calcula em qual quantidade de quebras os dois algoritmos têm custo mais próximo.
        limQuebrasIdx = 0;

        for (int i = 1; i < numLQ; i++)
        {
            double dif = fabs(custoQS[i].custo - custoINS[i].custo);
            if (dif < menorDif)
            {
                menorDif = dif;
                limQuebrasIdx = i;
            }
        }

        int newMin, newMax;
        if (limQuebrasIdx == 0)
        {
            newMin = 0;
            newMax = (numLQ >= 3) ? 2 : numLQ - 1;
        }
        else if (limQuebrasIdx == numLQ - 1)
        {
            newMin = (numLQ >= 3) ? numLQ - 3 : 0;
            newMax = numLQ - 1;
        }
        else
        {
            newMin = limQuebrasIdx - 1;
            newMax = limQuebrasIdx + 1;
        }

        minLQ = lqTestados[newMin];
        maxLQ = lqTestados[newMax];

        passoLQ = (maxLQ - minLQ) / 5;
        if (passoLQ == 0)
            passoLQ = 1;

        int posMin = newMin;
        int posMax = newMax;
        diffCusto = fabs(custoINS[posMin].custo - custoINS[posMax].custo); // Calcula a diferença de custo na nova faixa

        printf("numlq %d limQuebras %d lqdiff %.6lf\n", numLQ, lqTestados[limQuebrasIdx], diffCusto);

        cout << endl;
    }

    return lqTestados[limQuebrasIdx];
}
