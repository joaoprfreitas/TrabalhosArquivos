/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#include <file.h>

void setDadosRegistroFixo(FILE *file, char *csvFileName);
void setDadosRegistroVariavel(FILE *file, char *csvFileName);

/*
 * Cria um arquivo binário com o nome passado como parâmetro.
 * Retorna um ponteiro para o arquivo criado ou NULL no caso de um problema na criação.
 */
FILE *criarArquivoBinario(char *fileName) {
    FILE *f = fopen(fileName, "wb+");

    if (f == NULL) return NULL;

    return f;
}

/*
 * Verifica o tipo do arquivo, chamando a função correta
 * para setar o registro de cabeçalho desse tipo no arquivo binário.
 */
void setRegistroCabecalho(FILE *file, char *tipoArquivo) {
    if (!(strcmp(tipoArquivo, "tipo1"))) {
        setCabecalhoRegistroFixo(file, defaultCabecalhoFixo());
        return;
    }

    setCabecalhoRegistroVariavel(file, defaultCabecalhoVariavel());
}

/*
 * Verifica o tipo do arquivo, chamando a função correta
 * para setar os dados dos registros desse tipo.
 */
void preencherArquivoDados(FILE *file, char *tipoArquivo, char *csvFileName) {
    if (!(strcmp(tipoArquivo, "tipo1"))) {
        setDadosRegistroFixo(file, csvFileName);
        return;
    }

    setDadosRegistroVariavel(file, csvFileName);
}

/*
 * Abre um arquivo CSV com o nome passado como parâmetro.
 * Faz a leitura do cabeçalho do CSV, indo direto para o conteúdo.
 * 
 * Enquanto não chegar ao fim do csv:
 *  - Faz a leitura de uma linha do csv, salvando as infos na estrutura data_t.
 *  - Realiza o parsing das infos de data_t para a estrutura do registro fixo.
 *  - Escreve o registro fixo no arquivo binário.
 * 
 * Altera no cabeçalho do arquivo o campo proxRRN.
 */
void setDadosRegistroFixo(FILE *file, char *csvFileName) {
    FILE *csv = fopen(csvFileName, "r");
    if (csv == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    char *header = lerString(csv, CSV_ENDLINE, NULL);
    free(header);

    int proxRRN = 0; // Contador de RRNs armazenados
    while (true) {
        data_t data;
        if (!readLineCSV(csv, &data)) {
            break;
        }

        regFixo r = formatRegistroFixo(&data);

        addRegistroFixo(file, &r);
        proxRRN++;

        // Libera a memória auxiliar utilizada 
        free(r.cidade);
        free(r.marca);
        free(r.modelo);

        free(data.cidade);
        free(data.marca);
        free(data.modelo);
    }

    setProxRRN(file, proxRRN);

    fclose(csv);
}

/*
 * Abre um arquivo CSV com o nome passado como parâmetro.
 * Faz a leitura do cabeçalho do CSV, indo direto para o conteúdo.
 * 
 * Enquanto não chegar ao fim do csv:
 *  - Faz a leitura de uma linha do csv, salvando as infos na estrutura data_t.
 *  - Realiza o parsing das infos de data_t para a estrutura do registro de tamanho variável.
 *  - Escreve o registro variável no arquivo binário.
 * 
 * Altera no cabeçalho do arquivo o campo proxByteOffset.
 */
void setDadosRegistroVariavel(FILE *file, char *csvFileName) {
    FILE *csv = fopen(csvFileName, "r");
    if (csv == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    char *header = lerString(csv, CSV_ENDLINE, NULL);
    free(header);

    while (true) {
        data_t data;
        if (!readLineCSV(csv, &data)) {
            break;
        }

        regVariavel r = formatRegistroVariavel(&data);

        addRegistroVariavel(file, &r);

        // Libera a memória auxiliar utilizada
        free(r.cidade);
        free(r.marca);
        free(r.modelo);

        free(data.cidade);
        free(data.marca);
        free(data.modelo);
    }

    setProxByteOffset(file, ftell(file));

    fclose(csv);
}

/*
 * Abre um arquivo binário com o nome passado como parâmetro.
 * Retorna um ponteiro para o arquivo criado ou NULL no caso de um problema na abertura.
 */
FILE *abrirArquivoDados(char *fileName) {
    FILE *f = fopen(fileName, "rb");

    if (f == NULL) return NULL;

    return f;
}

/*
 * Faz a alteração do status no registro de cabeçalho do arquivo de dados.
 */
void setStatusSeguro(FILE *f) {
    fseek(f, 0, SEEK_SET);
    char status = '1';
    fwrite(&status, sizeof(char), 1, f);
}

/*
 * Retorna o status do arquivo de dados.
 */
char getStatus(FILE *f) {
    fseek(f, 0, SEEK_SET);
    char status;
    fread(&status, sizeof(char), 1, f);
    return status;
}

/*
 * Verifica se o arquivo está consistente.
 * Chama uma determinada função para cada tipo de registro.
 * Retorna:
 * - 0 se a leitura tiver ocorrido.
 * - -1 se não houver registros.
 * - -2 se o arquivo estiver inconsistente.
 */
int lerTodosRegistros(FILE *f, char *tipoArquivo) {
    if (getStatus(f) == '0') return -2; // Arquivo inconsistente

    if (!(strcmp(tipoArquivo, "tipo1"))) {
        return lerTodosRegistrosFixos(f);
    }

    return lerTodosRegistrosVariaveis(f);
}