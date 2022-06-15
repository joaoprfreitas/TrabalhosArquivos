/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <funcionalidades.h>
#include <funcoesFornecidas.h>
#include <funcoesFornecidas.h>

/*
 * Funcionalidade 1 do trabalho.
 *
 * Cria o arquivo de dados armazenando o cabeçalho e todos os
 * os registros (de acordo com o tipo) do arquivo CSV.
 */
void createTable(char *nomeArquivo, char *tipoArquivo, char *nomeCSV) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
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

    binarioNaTela(nomeArquivo);
}

/*
 * Funcionalidade 2 do trabalho.
 *
 * Realiza a impressão de todos os registro os registros
 * armazenados em um determinado arquivo.
 */
void listarTodosRegistros(char *nomeArquivo, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
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
 * Funcionalidade 3 do trabalho.
 *
 * Realiza a impressão dos registros pesquisados pelo campo.
 */
void listarCamposPesquisados(char* nomeArquivo, campos* n_campos, int numCampos, char* tipoArquivo){
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) { // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    buscarRegistroPorCampos(f, tipoArquivo, n_campos, numCampos);

    fclose(f);
}


/*
 * Funcionalidade 4 do trabalho.
 *
 * Realiza a impressão de um determinado registro fixo do arquivo
 * a partir de um dado RRN
 */
void getRegistroFixo(char *nomeArquivo, char *tipoArquivo, int RRN) {
    if (strcmp(tipoArquivo, "tipo1")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(f) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(f);
        return;
    }
    
    if (RRN > getNumeroRegistros(f) || RRN < 0) { // Verifica se o RRN é válido
        printf("Registro inexistente.\n");
        fclose(f);
        return;
    }

    regFixo *r = lerRegistroFixo(f, RRN);

    if (r->removido == '0') // Se o registro não estiver marcado como removido
        imprimirRegistroFixo(r);
    else
        printf("Registro inexistente.\n");
        
    freeRegistroFixo(r);

    fclose(f);
}
