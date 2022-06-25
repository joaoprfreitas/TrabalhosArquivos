/*
 * SSC0215 - 2022 - Organização de arquivos
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

    char parametro1[100];
    char parametro2[100];

    int RRN; // Valor do RRN a ser buscado
    int n; // Numero de campos

    campos* n_campos; // Vetor dos campos a serem buscados

    scanf("%d ", &funcionalidade);
    scanf("%s ", tipoArquivo);

    switch (funcionalidade) {
        case 1:
            scanf("%s ", parametro1); // nome csv
            scanf("%s\r\n", parametro2); // nome arquivo binario

            createTable(parametro2, tipoArquivo, parametro1);
            break;

        case 2:
            scanf("%s\r\n", parametro2); // nome arquivo binario

            listarTodosRegistros(parametro2, tipoArquivo);
            break;

        case 3:
            scanf("%s\r\n", parametro2); // nome arquivo binario
            scanf("%d", &n);

            n_campos = capturaCampos(n);
            listarCamposPesquisados(parametro2, n_campos, n, tipoArquivo);
            
            free(n_campos);
            break;
            
        case 4:
            scanf("%s ", parametro2); // nome arquivo binario
            scanf("%d\r\n", &RRN);

            getRegistroFixo(parametro2, tipoArquivo, RRN);
            break;

        case 5:
            scanf("%s ", parametro1); // nome do arquivo de dados
            scanf("%s\r\n", parametro2);  // nome arquivo de indice

            criarIndex(tipoArquivo, parametro1, parametro2);

            break;

        case 6:
            scanf("%s ", parametro1); // nome do arquivo de dados
            scanf("%s ", parametro2);  // nome arquivo de indice
            scanf("%d\r\n", &n); // numero de linhas a serem lidas

            for (int i = 0; i < n; i++) {
                int numCampos;
                scanf("%d ", &numCampos);

                n_campos = capturaCampos(numCampos);
                removerRegistros(tipoArquivo, parametro1, parametro2, n_campos, numCampos);

                free(n_campos);
            }

            break;

        case 7:

            break;

        case 8:
            
            break;

        case 9: // TESTE, REMOVER DPS
            scanf("%s\r\n", parametro1); // nome do arquivo de dados

            FILE *meu = fopen(parametro1, "rb");

            fseek(meu, 1, SEEK_SET);

            int id1;
            long long int byte1;

            long long int eof;

            do {
                fread(&id1, sizeof(int), 1, meu);
                eof = fread(&byte1, sizeof(long long int), 1, meu);

                printf("%d\n", id1);
                printf("%lld\n", byte1);

            } while (eof > 0);

            fclose(meu);

            break;
    
        default:
            break;
    }

    return EXIT_SUCCESS;
}
