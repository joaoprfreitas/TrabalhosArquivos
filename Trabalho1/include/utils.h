/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <funcoesFornecidas.h>
#include <constantes.h>

#define CSV_ENDLINE '\n'

typedef struct data_st {
    int id;
    int ano;
    int qtt;
    char sigla[2];

    char *cidade;
    char *marca;
    char *modelo;
} data_t;

typedef struct campos{
    char str1[100];
    char str2[100];
} campos;

char *lerString(FILE *f, char parada, bool *fimArquivo);
bool readLineCSV(FILE *csvFileName, data_t *data);

campos* capturaCampos(int n);
int buscaBinariaIndex(int id, index_t *index);

campos* capturaCamposUnitarios(int n);

int getTopo(FILE *arquivoDados);
void setTopo(FILE *arquivoDados, int topo);
int getNumRegRemovidos(FILE *arquivoDados);
void setNumRegRemovidos(FILE *arquivoDados, int numRemovidos);

#endif // UTILS_H
