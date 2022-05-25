/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <utils.h>

#define CSV_DELIMITER ","
#define CSV_COLS 7
#define BUFFER_SIZE 32

/* Faz a leitura de uma sequência de caracteres até achar o caracter de parada ou '\n' ou EOF.
 * Durante a leitura, suprime o '\r' caso houver.
 * Aloca em blocos de tamanho BUFFER_SIZE.
 * Caso encontre o EOF, altera 'fimArquivo' para true
 * Adiciona o '\0' no final da string criada.
 * Retorna a string.
 */
char *lerString(FILE *f, char parada, bool *fimArquivo) {
    char *linha = NULL, tmp;
    int cont = 0;

    do {
        tmp = getc(f);
        if (tmp == '\r') tmp = getc(f);

        if (cont % BUFFER_SIZE == 0) // Aloca em blocos de tamanho BUFFER_SIZE
            linha = realloc(linha, sizeof(char) * (cont + BUFFER_SIZE));

        if (tmp == parada) break;
        
        if (tmp == EOF) *fimArquivo = true;

        if ((tmp != '\n') && (tmp != EOF))
            linha[cont++] = tmp;

    } while ((tmp != '\n') && (tmp != EOF));

    linha[cont] = '\0';

    return linha;
}

/*
 * Faz a leitura de uma linha do arquivo CSV.
 * A partir da linha do CSV, realiza um split utilizando o delimitador CSV_DELIMITER.
 * Transforma os campos id, ano, qtt em inteiros.
 * Altera o parametro 'data' com os dados lidos, fazendo as seguintes verificações:
 *  - Para os campos ano e qtt, verifica se o valor existe, setando como -1 caso não exista.
 *  - Para o campo sigla, seta como lixo ('$$') caso esteja vazio.
 *  - Para os demais campos, faz um cópia dinâmica (strdup)
 * 
 * Retorna true se a leitura foi bem sucedida ou false caso tenha chegado ao fim do arquivo.
 */
bool readLineCSV(FILE *csv, data_t *data) {
    bool fimArquivo = false;
    char *token, *buffer;

    char *linha = lerString(csv, CSV_ENDLINE, &fimArquivo);
    buffer = linha; // Faz uma cópia para não perder a referência durante o strsep

    if (fimArquivo) {
        free(linha);
        return false;
    }

    int i = 0;

    /* strsep é para extrair os tokens de uma string separada por delimitadores
     * mesmo que algum field esteja vazio, o delimitador será considerado
     */
    while ((token = strsep(&buffer, CSV_DELIMITER)) != NULL) { // Enquanto houver tokens
        switch (i) {
            case 0:
                data->id = atoi(token);
                break;

            case 1:
                if (!(strcmp(token, "")))
                    data->ano = -1;
                else
                    data->ano = atoi(token);

                break;

            case 2:
                data->cidade = strdup(token); // Cria dinamicamente uma cópia da string
                break;

            case 3:
                if (!(strcmp(token, "")))
                    data->qtt = -1;
                else
                    data->qtt = atoi(token);

                break;

            case 4:
                if (!(strcmp(token, ""))) { // Altera para lixo caso esteja vazio
                    data->sigla[0] = '$';
                    data->sigla[1] = '$';
                } else    
                    strcpy(data->sigla, token);
                    
                break;

            case 5:
                data->marca = strdup(token);
                break;

            case 6:
                data->modelo = strdup(token);
                break;
        }
        i++;
    }

    free(linha);

    return true;
}

/*
 *  Faz a leitura dos campos a serem pesquisados.
 *  Retorna o vetor de campos a serem pesquisados. 
*/

campos* capturaCampos(int n){
    campos* n_campos = malloc(n * sizeof(campos));
    
    // Faz a leitura dos n campos
    for (int i = 0; i < n; i++) {
        scanf("%s ", n_campos[i].str1);
        scan_quote_string(n_campos[i].str2);
    }    

    return n_campos;
}