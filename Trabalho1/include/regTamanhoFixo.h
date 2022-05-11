/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#ifndef REGTAMANHOFIXO_H
#define REGTAMANHOFIXO_H

#include <string.h>
#include <stdio.h>

#define TAM_DESCRICAO 40
#define TAM_DESC1 22
#define TAM_DESC2 19
#define TAM_DESC3 24
#define TAM_DESC4 8
#define TAM_DESC5 16
#define TAM_DESC6 18
#define TAM_DESC7 19
#define TAM_SIGLA 2

// Deve ocupar 182 bytes no arquivo
typedef struct regCabecalhoFixo {
    char status; // '0' para inconsistente, '1' para consistente
    int topo;
    
    char descricao[TAM_DESCRICAO + 1];
    char desC1[TAM_DESC1 + 1];
    char desC2[TAM_DESC2 + 1];
    char desC3[TAM_DESC3 + 1];
    char desC4[TAM_DESC4 + 1];

    char codC5;
    char desC5[TAM_DESC5 + 1]; 
    char codC6;
    char desC6[TAM_DESC6 + 1];
    char codC7;
    char desC7[TAM_DESC7 + 1]; 

    int proxRRN;
    int nroRegRem;

} regCabecalhoFixo;

// Deve ocupar 97 bytes
typedef struct regTamanhoFixo {
    char removido;
    int prox;
    int id;
    int ano;
    int qtt;
    char sigla[TAM_SIGLA + 1];
    int tamCidade;
    char codC5;
    char *cidade;
    int tamMarca;
    char codC6;
    char *marca;
    int tamModelo;
    char codC7;
    char *modelo;
} regFixo;

regCabecalhoFixo defaultCabecalhoFixo();
void setDefaultCabecalhoFixo(FILE *, regCabecalhoFixo);

#endif // #REGTAMANHOFIXO_H