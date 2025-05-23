#ifndef ESTATISTICAS
#define ESTATISTICAS

typedef struct {
    int comparacoes;
    int trocas;
    int minParticao;
    int chamadas;
    double custo;

    // For break threshold testing
    double custoInsercao;
    int comparacoesInsercao;
    int trocasInsercao;
    int chamadasInsercao;

} Estatistica;

#endif