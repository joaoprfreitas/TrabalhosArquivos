/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <funcionalidades.h>
#include <funcoesFornecidas.h>

int main() {
    int funcionalidade;
    char tipoArquivo[20];

    char nomeCSV[100];
    char nomeArquivoBinario[100];

    int RRN; // Valor do RRN a ser buscado
    int n; // Numero de campos

    campos* n_campos; // Vetor dos campos a serem buscados

    scanf("%d ", &funcionalidade);
    scanf("%s ", tipoArquivo);

    switch (funcionalidade) {
        case 1:
            scanf("%s ", nomeCSV);
            scanf("%s\r\n", nomeArquivoBinario);

            createTable(nomeArquivoBinario, tipoArquivo, nomeCSV);
            break;

        case 2:
            scanf("%s\r\n", nomeArquivoBinario);

            listarTodosRegistros(nomeArquivoBinario, tipoArquivo);
            break;

        case 3:
            scanf("%s\r\n", nomeArquivoBinario);
            scanf("%d", &n);

            n_campos = capturaCampos(n);
            listarCamposPesquisados(nomeArquivoBinario, n_campos, n, tipoArquivo);
            
            free(n_campos);
            break;
            
        case 4:
            scanf("%s ", nomeArquivoBinario);
            scanf("%d\r\n", &RRN);

            getRegistroFixo(nomeArquivoBinario, tipoArquivo, RRN);
            break;
    
        default:
            break;
    }

    return EXIT_SUCCESS;
}
