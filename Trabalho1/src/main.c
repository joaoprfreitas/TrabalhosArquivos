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

    campos *n_campos; // Vetor dos campos a serem buscados
    campos **camposBuscados;

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

            camposBuscados = malloc(sizeof(campos *) * n);
            int *numCampos = malloc(sizeof(int) * n);

            for (int i = 0; i < n; i++) {
                scanf("%d ", &numCampos[i]);
                camposBuscados[i] = capturaCampos(numCampos[i]);
            }

            removerRegistros(tipoArquivo, parametro1, parametro2, camposBuscados, numCampos, n);

            for (int i = 0; i < n; i++) {
                free(camposBuscados[i]);
            }

            free(camposBuscados);
            free(numCampos);

            break;

        case 7:
            // scanf("%s ", parametro1); // nome do arquivo de dados
            // scanf("%s ", parametro2);  // nome arquivo de indice

            // scanf("%d\r\n", &n); // numero de registros a serem inseridos
            // campos* n_campos = capturaCamposUnitarios(7);

            // insereCampos(tipoArquivo, n_campos, parametro1);

            break;

        case 8:
            
            break;

        case 9: // TESTE, REMOVER DPS
            scanf("%s\r\n", parametro1); // nome do arquivo de dados

            FILE *meu = fopen(parametro1, "rb");

            fseek(meu, 1, SEEK_SET);

            int id1;
            int rrn;
            int eof;

            do {
                fread(&id1, sizeof(int), 1, meu);
                eof = fread(&rrn, sizeof(int), 1, meu);

                printf("%d %d\n", id1, rrn);

            } while (eof != 0);

            fclose(meu);

            break;
    
        default:
            break;
    }

    return EXIT_SUCCESS;
}
