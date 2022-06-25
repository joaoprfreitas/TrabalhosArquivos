/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#ifndef REGTAMANHOVARIAVEL_H
#define REGTAMANHOVARIAVEL_H

#include <stdio.h>
#include <funcionalidades.h>
#include <string.h>
#include <utils.h>
#include <constantes.h>

#define TAM_CABECALHO_VARIAVEL 190

#define TAM_DESCRICAO 40
#define TAM_DESC1 22
#define TAM_DESC2 19
#define TAM_DESC3 24
#define TAM_DESC4 8
#define TAM_DESC5 16
#define TAM_DESC6 18
#define TAM_DESC7 19

#define TAM_SIGLA 2

// Deve ocupar 190 bytes no arquivo
typedef struct regCabecalhoVariavel {
    char status; // '0' para inconsistente, '1' para consistente
    long long int topo; // armazena o byte offset do registro que está no topo da pilha
    
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

    long long int proxByteOffset;
    int nroRegRem;

} regCabecalhoVariavel;

// Deve ocupar 97 bytes
typedef struct regTamanhoVariavel {
    char removido;
    int tamanhoRegistro;
    long long int prox;
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
} regVariavel;

regCabecalhoVariavel defaultCabecalhoVariavel();
void setCabecalhoRegistroVariavel(FILE *, regCabecalhoVariavel);

void addRegistroVariavel(FILE *f, regVariavel *r);
regVariavel formatRegistroVariavel(data_t *data);
int lerTodosRegistrosVariaveis(FILE *f);

long long int getProxByteOffset(FILE *f);
void setProxByteOffset(FILE *f, long long int proxByteOffset);

int verificaCamposVariaveis(regVariavel*, campos*, int totalCampos);

regVariavel *lerRegistroVariavel(FILE *f);
void imprimirRegistroVariavel(regVariavel *r);
void freeRegistroVariavel(regVariavel *r);

void realizarIndexacaoRegVariavel(FILE *dados, FILE *index);

#endif // #REGTAMANHOFIXO_H
