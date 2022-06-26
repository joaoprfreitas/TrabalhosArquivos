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
            scanf("%s ", parametro1); // nome do arquivo de dados
            scanf("%s ", parametro2);  // nome arquivo de indice

            scanf("%d\r\n", &n); // numero de registros a serem inseridos

            data_t *data = malloc(sizeof(data_t) * n);

            for (int i = 0; i < n; i++) {
                data[i] = lerLinhaDadosInserir();
            }

            insereRegistros(tipoArquivo, parametro1, parametro2, data, n);

            for (int i = 0; i < n; i++) {
                free(data[i].cidade);
                free(data[i].marca);
                free(data[i].modelo);
            }

            free(data);

            break;

        case 8:
            scanf("%s ", parametro1); // nome do arquivo de dados
            scanf("%s ", parametro2);  // nome arquivo de indice
            scanf("%d\r\n", &n); // numero de linhas a serem lidas

            camposBuscados = malloc(sizeof(campos *) * n);
            campos **novosValores = malloc(sizeof(campos *) * n);

            numCampos = malloc(sizeof(int) * n);
            int *numCamposNovosValores = malloc(sizeof(int) * n);

            for (int i = 0; i < n; i++) {
                scanf("%d ", &numCampos[i]);
                camposBuscados[i] = capturaCampos(numCampos[i]);
                scanf("%d ", &numCamposNovosValores[i]);
                novosValores[i] = capturaCampos(numCampos[i]);
            }

            // for (int i = 0; i < n; i++) {
                
            //     printf("BUSCA: ");
            //     for (int j = 0; j < numCampos[i]; j++) {
            //         printf("%s %s|", camposBuscados[i][j].str1, camposBuscados[i][j].str2);
            //     }
            //     printf("\n");

            //     printf("NOVOS VALORES: ");
            //     for (int j = 0; j < numCamposNovosValores[i]; j++) {
            //         printf("%s %s|", novosValores[i][j].str1, novosValores[i][j].str2);
            //     }
            //     printf("\n");
            // }

            atualizarRegistros(tipoArquivo, parametro1, parametro2, camposBuscados, numCampos, novosValores, numCamposNovosValores, n);

            for (int i = 0; i < n; i++) {
                free(camposBuscados[i]);
                free(novosValores[i]);
            }

            free(camposBuscados);
            free(numCampos);
            free(novosValores);
            free(numCamposNovosValores);
            
            break;

        case 9: // TESTE, REMOVER DPS
            scanf("%s\r\n", parametro1); // nome do arquivo de indice

            FILE *meu = fopen(parametro1, "rb");

            fseek(meu, 1, SEEK_SET);

            int id1, rrn, eof;

            do {
                fread(&id1, sizeof(int), 1, meu);
                eof = fread(&rrn, sizeof(int), 1, meu);

                printf("%d %d\n", id1, rrn);

            } while (eof != 0);

            fclose(meu);

            break;

        case 10:
            scanf("%s\r\n", parametro1); // nome do arquivo binario
            
            FILE *f = fopen(parametro1, "rb");
            fseek(f, 20125, SEEK_SET);
            char removido;
            int tamanho;
            long long int prox;

            fread(&removido, sizeof(char), 1, f);
            fread(&tamanho, sizeof(int), 1, f);
            fread(&prox, sizeof(long long int), 1, f);

            printf("%c %d %lld\n", removido, tamanho, prox);

            fclose(f);

            break;
    
        default:
            break;
    }

    return EXIT_SUCCESS;
}
