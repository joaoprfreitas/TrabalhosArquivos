/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#ifndef FUNCIONALIDADES
#define FUNCIONALIDADES

#include <stdio.h>
#include <file.h>
#include <utils.h>

void createTable(char *fileName, char *tipoArquivo, char *csvFileName);
void listarTodosRegistros(char *binFileName, char *tipoArquivo);
void getRegistroFixo(char *nomeArquivoBinario, char *tipoArquivo, int RRN);
void listarCamposPesquisados(char* nomeArquivoBinario, campos*, int numCampos, char* tipoArquivo);

#endif // FUNCIONALIDADES
