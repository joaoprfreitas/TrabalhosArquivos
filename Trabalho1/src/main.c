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
    char nomeBin[100];
    int RRN;

    scanf("%d ", &funcionalidade);
    scanf("%s ", tipoArquivo);

    switch (funcionalidade) {
        case 1:
            scanf("%s ", nomeCSV);
            scanf("%s\r\n", nomeBin);

            createTable(nomeBin, tipoArquivo, nomeCSV);

            binarioNaTela(nomeBin);
            break;
        case 2:
            scanf("%s\r\n", nomeBin);

            listarTodosRegistros(nomeBin, tipoArquivo);
            
            break;
        case 3:
            /* code */
            break;
        case 4:
            scanf("%s ", nomeBin);
            scanf("%d\r\n", &RRN);
            getRegistroFixo(nomeBin, tipoArquivo, RRN);
            
            break;
    
        default:
            break;
    }

    

    return EXIT_SUCCESS;
}