/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <utils.h>
#include <string.h>
#include <regTamanhoFixo.h>
#include <regTamanhoVariavel.h>

FILE *criarArquivoBinario(char *fileName);
void setRegistroCabecalho(FILE *fileName, char *tipoArquivo);
void preencherArquivoDados(FILE *file, char *tipoArquivo, char *csvFileName);
FILE *abrirArquivoDados(char *fileName);

int lerTodosRegistros(FILE *f, char *tipoArquivo);

char getStatus(FILE *f);
void setStatusConsistente(FILE *f);
void setStatusInconsistente(FILE *f);

void buscarRegistroPorCampos(FILE *f, char *tipoArquivo, campos* n_campos, int numCampos);

void realizarIndexacao(char *tipoArquivo, FILE *dados, FILE *index);

#endif // FILE_H
