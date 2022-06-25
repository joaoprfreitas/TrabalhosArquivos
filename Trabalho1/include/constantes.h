#ifndef CONSTANTES_H
#define CONSTANTES_H

typedef struct campoIndex_st {
    int id;
    long long int posicao;
} campoIndex_t;

typedef struct index_st {
    campoIndex_t *lista;
    int tamanho;
} index_t;

#define CABECALHO_TOPO 1
#define CABECALHO_NUM_REG_REMOVIDOS_FIXO 178
#define CABECALHO_NUM_REG_REMOVIDOS_VARIAVEL 186

#endif