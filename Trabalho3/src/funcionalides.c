/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <funcionalidades.h>
#include <funcoesFornecidas.h>
#include <funcoesFornecidas.h>
#include <utils.h>
#include <arvoreB.h>

/*
 * Funcionalidade 9 do trabalho.
 *
 * Cria o arquivo de indices de um determinado arquivos de dados
 * utilizando uma árvore B.
 */
void criarIndexArvoreB(char *tipoArquivo, char *arquivoDados, char *arquivoIndice) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *dados = abrirArquivoDados(arquivoDados);
    FILE *index = criarArquivoBinario(arquivoIndice);

    if (dados == NULL || index == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(dados) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(dados);
        return;
    }

    criarRegistroCabecalho(index, tipoArquivo);

    // realizarIndexacao(tipoArquivo, dados, index);

    setStatusConsistente(index); // Marca o arquivo como consistente

    fclose(dados);
    fclose(index);

    binarioNaTela(arquivoIndice);
}

/*
 * Funcionalidade 10 do trabalho.
 *
 * Realiza a busca de registros no arquivo de dados por meio do ID, utilizando a estrutura
 * da árvore B.
 */
void buscarRegistro(char *tipoArquivo, char *arquivoDados, char *arquivoIndice, int id) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *dados = abrirArquivoDados(arquivoDados);
    FILE *index = abrirArquivoDados(arquivoIndice);

    if (dados == NULL || index == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(dados) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(dados);
        return;
    }

    if (getStatus(index) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(index);
        return;
    }

    buscarRegistroIndex(dados, index, tipoArquivo, id);

    fclose(dados);
    fclose(index);
}