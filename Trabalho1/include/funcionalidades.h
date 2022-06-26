/*
 * SSC0215 - 2022 - Organização de arquivos
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
void criarIndex(char *tipoArquivo, char *arquivoDados, char *arquivoIndice);
void removerRegistros(char *tipoArquivo, char *arquivoDados, char *arquivoIndice, campos **camposBuscados, int *numCamposPorLinha, int numLinhas);
void insereRegistros(char* tipoArquivo, char *nomeArquivoDados, char *nomeArquivoIndice, data_t *data, int numRegistros);
void atualizarRegistros(char *tipoArquivo, char *nomeArquivoDados, char *nomeArquivoIndice, campos **camposBuscados, int *numCamposPorLinha, campos **novosValores, int *numCamposPorLinhaNovosValores, int numLinhas);



#endif // FUNCIONALIDADES
