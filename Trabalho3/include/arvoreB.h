#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdio.h>
#include <stdlib.h>

#define ORDEM_ARVORE_B 4

#define POS_NO_RAIZ 1
#define POS_PROX_RRN 5
#define POS_NUM_NOS 9

#define TAM_NO_FIXO 45
#define TAM_NO_VARIAVEL 57

typedef struct pagina_st {
    char tipoNo;
    int numChaves;
    // Fazer cast para int ao escrever
    long long int chaves[ORDEM_ARVORE_B - 1][2]; // [0] = valor, [1] = pos (rrn ou byteoffset)
    int filhos[ORDEM_ARVORE_B];
} pagina;

typedef struct no_fixo_st {
    char tipoNo;
    int numChaves;

    int C1; // id
    int PR1; // rrn no arq dados

    int C2;
    int PR2;

    int C3;
    int PR3;

    int P1;
    int P2;
    int P3;
    int P4;
} no_fixo;

typedef struct no_var_st {
    char tipoNo; // 0 = no raiz, 1 = nó intermediario, 2 = nó folha
    int numChaves;

    int C1; // id
    long long int PR1; // byteoffset no arq dados

    int C2;
    long long int PR2;

    int C3;
    long long int PR3;

    int P1;
    int P2;
    int P3;
    int P4;
} no_variavel;

void criarRegistroCabecalho(FILE *f, char *tipoArquivo);
pagina lerPaginaDisco(FILE *f, char *tipoArquivo, int RRN);
void buscaArvoreB(FILE *f, char *tipoArquivo, int RRN, int chave, int *paginaEncontrada_RRN, int *posChaveNaPagina);

void setNoRaiz(FILE *f, int noRaiz);
int getNoRaiz(FILE *f);

void setProxRRNArvore(FILE *f, int proxRRN);
int getProxRRNArvore(FILE *f);

void setNumNos(FILE *f, int numNos);
int getNumNos(FILE *f);

#endif