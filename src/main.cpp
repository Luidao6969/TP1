#include "../include/Ordenador.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>

void lerArquivo(const char* nomeArquivo, int*& V, int& tam, double& a, double& b, double& c) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    int seed;
    double limiarCusto;

    // Ler os 6 primeiros valores corretamente
    fscanf(arquivo, "%d", &seed);           // 1. semente aleatória
    fscanf(arquivo, "%lf", &limiarCusto);   // 2. limiar de convergência
    fscanf(arquivo, "%lf", &a);             // 3. coeficiente a
    fscanf(arquivo, "%lf", &b);             // 4. coeficiente b
    fscanf(arquivo, "%lf", &c);             // 5. coeficiente c
    fscanf(arquivo, "%d", &tam);            // 6. tamanho do vetor

    // Opcionalmente usar a semente, se necessário
    srand(seed);

    // Validar tamanho
    if (tam <= 0) {
        fprintf(stderr, "Tamanho de vetor inválido: %d\n", tam);
        exit(1);
    }

    // Alocar e ler vetor
    V = new int[tam];
    for (int i = 0; i < tam; i++) {
        fscanf(arquivo, "%d", &V[i]);
    }

    fclose(arquivo);
}

int main() {
    int* vetor = nullptr;
    int tam;
    double a, b, c;
    
    // Ler dados do arquivo
    lerArquivo("teste1.txt", vetor, tam, a, b, c);
    
    // Criar ordenador
    Ordenador o(a, b, c);
    
    // Determinar limiar ótimo
    int limiarOtimo = o.determinaLimiarParticao(vetor, tam, 10);
    o.determinaLimiarQuebras(vetor, tam, 10, limiarOtimo, 1);
    //int quebraOtimo = o.determinaLimiarQuebras(vetor, tam, 10, 10);

    
    printf("Limiar ótimo de partição: %d\n", limiarOtimo);
    
    delete[] vetor;
    return 0;
}
