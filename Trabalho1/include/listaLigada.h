#ifndef LISTALIGADA_H
#define LISTALIGADA_H

typedef struct no_t {
    int tamanhoRegistro;
    int proxRegistroDisponivel;
    struct no_t *prox;
} no;

typedef struct {
    no *cabeca;
    no *cauda;
} listaLigada;


#endif