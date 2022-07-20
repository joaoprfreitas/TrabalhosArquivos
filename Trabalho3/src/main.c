/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 * 
 * Participação:
 *  - João Pedro Rodrigues Freitas: 100%
 *  - Guilherme Pacheco de Oliveira Souza: 0%
 */

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <funcionalidades.h>
#include <funcoesFornecidas.h>

int main() {
    int funcionalidade;
    char tipoArquivo[20];

    char parametro1[100];
    char parametro2[100];

    int id; // ID do registro a ser buscado

    char aux[10];

    scanf("%d ", &funcionalidade);
    scanf("%s ", tipoArquivo);

    switch (funcionalidade) {
        case 9:

            break;

        case 10:
            scanf("%s ", parametro1); // nome do arquivo de dados
            scanf("%s ", parametro2);  // nome arquivo de indice
            scanf("%s", aux); // meio de busca (ID)
            scanf("%d", &id); // valor do ID

            buscarRegistro(tipoArquivo, parametro1, parametro2, id);

            break;

        case 11:

            break;
    
        default:
            break;
    }

    return EXIT_SUCCESS;
}
