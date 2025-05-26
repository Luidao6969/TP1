#ifndef ESTATISTICAS
#define ESTATISTICAS

typedef struct {

    int comparacoes;
    int trocas;
    int minParticao;
    int chamadas;
    double custo;

    //Para a comparação dupla entre QuickSort e InsertionSort
    double custoInsercao;
    int comparacoesInsercao;
    int trocasInsercao;
    int chamadasInsercao;

} Estatistica;

#endif