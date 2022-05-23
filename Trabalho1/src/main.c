/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <stdio.h>
#include <stdlib.h>
#include <funcionalidades.h>
#include <funcoesFornecidas.h>

int main() {
    int funcionalidade;
    char tipoArquivo[20];

    char nomeCSV[100];
    char nomeArquivoBinario[100];

    int RRN;

    scanf("%d ", &funcionalidade);
    scanf("%s ", tipoArquivo);

    switch (funcionalidade) {
        case 1:
            scanf("%s ", nomeCSV);
            scanf("%s\r\n", nomeArquivoBinario);

            createTable(nomeArquivoBinario, tipoArquivo, nomeCSV);

            binarioNaTela(nomeArquivoBinario);
            break;

        case 2:
            scanf("%s\r\n", nomeArquivoBinario);

            listarTodosRegistros(nomeArquivoBinario, tipoArquivo);
            break;

        case 3:
            /* code */
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