/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#ifndef FILE_H
#define FILE_H

//#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <string.h>
#include <regTamanhoFixo.h>
#include <regTamanhoVariavel.h>

typedef struct data_st {
    int id;
    int ano;
    int qtt;
    char sigla[2];

    char *cidade;
    char *marca;
    char *modelo;
} data_t;



#endif // FILE_H