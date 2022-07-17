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

            camposBuscados = malloc(sizeof(campos *) * n); // Cria um vetor para as informações de cada linha
            int *numCampos = malloc(sizeof(int) * n); // Cria um vetor para o numero de campos de cada linha

            for (int i = 0; i < n; i++) { // Preenche o vetor com as informações de cada linha
                scanf("%d ", &numCampos[i]);
                camposBuscados[i] = capturaCampos(numCampos[i]);
            }

            removerRegistros(tipoArquivo, parametro1, parametro2, camposBuscados, numCampos, n);

            // Libera a memória auxiliar utilizada
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

            data_t *data = malloc(sizeof(data_t) * n); // Cria um vetor para as informações de cada linha

            // Preenche o vetor com as informações de cada linha
            for (int i = 0; i < n; i++) {
                data[i] = lerLinhaDadosInserir();
            }

            insereRegistros(tipoArquivo, parametro1, parametro2, data, n);

            // Libera a memória auxiliar utilizada
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

            camposBuscados = malloc(sizeof(campos *) * n); // Cria um vetor para as informações de busca
            campos **novosValores = malloc(sizeof(campos *) * n); // Cria um vetor para os novos campos

            numCampos = malloc(sizeof(int) * n); // Cria um vetor para o numero de campos de cada busca
            int *numCamposNovosValores = malloc(sizeof(int) * n); // Cria um vetor para o numero de campos de cada novos campos

            // Preenche os vetores com as informações de cada par de linhas
            for (int i = 0; i < n; i++) {
                // 1a linha da entrada
                scanf("%d ", &numCampos[i]);
                camposBuscados[i] = capturaCampos(numCampos[i]);
                // 2a linha da entrada
                scanf("%d ", &numCamposNovosValores[i]);
                novosValores[i] = capturaCampos(numCampos[i]);
            }

            atualizarRegistros(tipoArquivo, parametro1, parametro2, camposBuscados, numCampos, novosValores, numCamposNovosValores, n);

            // Libera a memória auxiliar utilizada
            for (int i = 0; i < n; i++) {
                free(camposBuscados[i]);
                free(novosValores[i]);
            }

            free(camposBuscados);
            free(numCampos);
            free(novosValores);
            free(numCamposNovosValores);
            
            break;

        case 9:

            break;

        case 10:

            break;

        case 11:

            break;
    
        default:
            break;
    }

    return EXIT_SUCCESS;
}
