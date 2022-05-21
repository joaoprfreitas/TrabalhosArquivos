/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
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

FILE *createFile(char *fileName);
void setRegistroCabecalho(FILE *fileName, char *tipoArquivo);
void setFileData(FILE *file, char *tipoArquivo, char *csvFileName);


#endif // FILE_H