#ifndef FUNCIONALIDADES
#define FUNCIONALIDADES

#include <stdio.h>
#include <file.h>

void createTable(char *fileName, char *tipoArquivo, char *csvFileName);
void listarTodosRegistros(char *binFileName, char *tipoArquivo);
void getRegistroFixo(char *nomeArquivoBinario, char *tipoArquivo, int RRN);

#endif // FUNCIONALIDADES