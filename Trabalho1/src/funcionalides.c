/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <funcionalidades.h>

/*
 * Funcionalidade 1 do trabalho.
 *
 * Cria o arquivo de dados armazenando o cabeçalho e todos os
 * os registros (de acordo com o tipo) do arquivo CSV.
 */
void createTable(char *nomeArquivo, char *tipoArquivo, char *nomeCSV) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *file = criarArquivoBinario(nomeArquivo);

    if (file == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    setRegistroCabecalho(file, tipoArquivo);

    preencherArquivoDados(file, tipoArquivo, nomeCSV);

    setStatusSeguro(file);

    fclose(file);
}

/*
 * Funcionalidade 2 do trabalho.
 *
 * Realiza a impressão de todos os registro os registros
 * armazenados em um determinado arquivo.
 */
void listarTodosRegistros(char *nomeArquivo, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);
    
    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    int codigo = lerTodosRegistros(f, tipoArquivo);

    if (codigo == -1)
        printf("Registro inexistente.\n");
    else if (codigo == -2)
        printf("Falha no processamento do arquivo.\n");

    fclose(f);
}

/*
 * Funcionalidade 4 do trabalho.
 *
 * Realiza a impressão de um determinado registro fixo do arquivo
 * a partir de um dado RRN
 */
void getRegistroFixo(char *nomeArquivo, char *tipoArquivo, int RRN) {
    if (strcmp(tipoArquivo, "tipo1")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(f) == '0' || RRN < 0) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    if (RRN > getNumeroRegistros(f)) {
        printf("Registro inexistente.\n");
        return;
    }

    regFixo *r = lerRegistroFixo(f, RRN);

    if (r->removido == '0')
        imprimirRegistroFixo(r);
    else
        printf("Registro inexistente.\n");
        
    freeRegistroFixo(r);

    fclose(f);
}