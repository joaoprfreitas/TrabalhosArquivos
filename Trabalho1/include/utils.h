/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char *lerString(FILE *f, char parada, bool *fimArquivo);
bool readLineCSV(FILE *csvFileName, data_t *data);

#endif // UTILS_H
