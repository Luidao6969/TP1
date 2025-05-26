#include "../include/Ordenador.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

typedef struct {
    int seed;
    double limiarCusto;
} Custos;

void lerArquivo(const char* nomeArquivo, int*& V, int& tam, double& a, double& b, double& c, Custos& custo) {
    cout << "Tentando abrir arquivo: '" << nomeArquivo << "'" << endl;
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    fscanf(arquivo, "%d", &custo.seed);
    fscanf(arquivo, "%lf", &custo.limiarCusto);
    fscanf(arquivo, "%lf", &a);
    fscanf(arquivo, "%lf", &b);
    fscanf(arquivo, "%lf", &c);
    fscanf(arquivo, "%d", &tam);

    srand(custo.seed);

    if (tam <= 0) {
        fprintf(stderr, "Tamanho de vetor inválido: %d\n", tam);
        exit(1);
    }

    V = new int[tam];
    for (int i = 0; i < tam; i++) {
        fscanf(arquivo, "%d", &V[i]);
    }

    fclose(arquivo);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nome_arquivo>" << endl;
        // Adicione isso para debug no VPL:
        cerr << "Argumentos recebidos: " << argc << endl;
        for (int i = 0; i < argc; i++) {
            cerr << "argv[" << i << "] = " << argv[i] << endl;
        }
        return 1;
    }

    const char* nomeArquivo = argv[1];

    int* vetor = nullptr;
    int tam;
    double a, b, c;
    Custos custo;

    // Ler dados do arquivo
    lerArquivo(nomeArquivo, vetor, tam, a, b, c, custo);

    // Criar ordenador
    Ordenador o(a, b, c);
    double custo1 = custo.limiarCusto;
    int seed1 = custo.seed;

    // Conta as quebras
    int quebras = o.contarQuebras(vetor, tam);

    cout << "size " << tam << " seed " << seed1 << " breaks " << quebras << endl;
    cout << endl;

    // Determinar limiar ótimo
    int limiarOtimo = o.determinaLimiarParticao(vetor, tam, custo1);
    o.determinaLimiarQuebras(vetor, tam, custo1, limiarOtimo, seed1);

    delete[] vetor;
    return 0;
}
