/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#ifndef FUNCIONALIDADES
#define FUNCIONALIDADES

typedef struct campos{
    char *str1;
    char *str2;

}campos;



#include <stdio.h>
#include <file.h>

void createTable(char *fileName, char *tipoArquivo, char *csvFileName);
void listarTodosRegistros(char *binFileName, char *tipoArquivo);
void getRegistroFixo(char *nomeArquivoBinario, char *tipoArquivo, int RRN);
campos* capturaCampos(int n);
void liberaCampos(campos*, int n);
int listarCamposPesquisados(char* nomeArquivoBinario, campos*, int numCampos, char* tipoArquivo);
#endif // FUNCIONALIDADES
