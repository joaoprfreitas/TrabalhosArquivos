#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct data_st {
    int id;
    int ano;
    int qtt;
    char sigla[2];

    char *cidade;
    char *marca;
    char *modelo;
} data_t;

#endif // UTILS_H