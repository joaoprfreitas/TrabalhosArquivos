/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <utils.h>

#define CSV_DELIMITER ','
#define CSV_COLS 7
#define BUFFER_SIZE 32

/* Faz a leitura de uma sequência de caracteres até achar o caracter de parada ou '\n' ou EOF.
 * Durante a leitura, suprime o '\r' caso houver.
 * Aloca em blocos de tamanho BUFFER_SIZE, até tam_max.
 * Caso encontre o EOF, altera a bool para true
 * Adiciona o '\0' no final da string criada, retornando o ponteiro.
 */
char *lerString(FILE *f, char parada, bool *fimArquivo) {
    char *linha = NULL, tmp;
    int cont = 0;

    do {
        tmp = getc(f);
        if (tmp == '\r') tmp = getc(f);

        if (cont % BUFFER_SIZE == 0)
            linha = realloc(linha, sizeof(char) * (cont + BUFFER_SIZE));

        if (tmp == parada) break;
        
        if (tmp == EOF) *fimArquivo = true;

        if ((tmp != '\n') && (tmp != EOF))
            linha[cont++] = tmp;

    } while ((tmp != '\n') && (tmp != EOF));

    linha[cont] = '\0';

    return linha;
}

data_t *readCSV(char *name) {
    data_t *data;

    FILE *f = fopen(name, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    bool fimArquivo = false;

    while(!fimArquivo) {
        //TODO
    }

}


    
    

// char *lerLinha(char parada, bool *fimArquivo) {
//     char *linha = NULL, tmp;
//     int cont = 0;

//     do {
//         tmp = getchar();
//         if (tmp == '\r') tmp = getchar();

//         if (cont % BUFFER_SIZE == 0)
//             linha = realloc(linha, sizeof(char) * (cont + BUFFER_SIZE));

//         if (tmp == parada) break;
        
//         if (tmp == EOF) *fimArquivo = true;

//         if ((tmp != '\n') && (tmp != EOF))
//             linha[cont++] = tmp;

//     } while ((tmp != '\n') && (tmp != EOF));

//     linha[cont] = '\0';

//     return linha;
// }