/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#include <file.h>

void setDataRegistroFixo(FILE *file, char *csvFileName);
void setDataRegistroVariavel(FILE *file, char *csvFileName);
char getStatus(FILE *f);

// TODO: QUANDO FOR FECHAR O ARQUIVO, SETAR NO STATUS NO ARQUIVO PARA '1'
void setRegistroCabecalho(FILE *file, char *tipoArquivo) {
    // Seta tipo 1
    if (!(strcmp(tipoArquivo, "tipo1"))) {
        regCabecalhoFixo aa = defaultCabecalhoFixo();
        
        setDefaultCabecalhoFixo(file, defaultCabecalhoFixo());
        return;
    }

    // Seta tipo 2
    setDefaultCabecalhoVariavel(file, defaultCabecalhoVariavel());
    
}

FILE *createFile(char *fileName) {
    FILE *f = fopen(fileName, "wb");
    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return f;
}

void setFileData(FILE *file, char *tipoArquivo, char *csvFileName) {
    if (!(strcmp(tipoArquivo, "tipo1"))) {
        setDataRegistroFixo(file, csvFileName);
        return;
    }

    setDataRegistroVariavel(file, csvFileName);
}

void setDataRegistroFixo(FILE *file, char *csvFileName) {
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

        regFixo r = formatRegistroFixo(&data);

        addRegistroFixo(file, &r);

        free(r.cidade);
        free(r.marca);
        free(r.modelo);

        free(data.cidade);
        free(data.marca);
        free(data.modelo);
    }

    fclose(csv);
}

void setDataRegistroVariavel(FILE *file, char *csvFileName) {
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

        free(r.cidade);
        free(r.marca);
        free(r.modelo);

        free(data.cidade);
        free(data.marca);
        free(data.modelo);
    }

    fclose(csv);
}

FILE *openBinFile(char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return f;
}

char getStatus(FILE *f) {
    fseek(f, 0, SEEK_SET);
    char status;
    fread(&status, sizeof(char), 1, f);
    return status;
}

int lerTodosRegistros(FILE *f, char *tipoArquivo) {
    if (getStatus(f) == '0') return -2; // Arquivo inconsistente

    if (!(strcmp(tipoArquivo, "tipo1"))) {
        return lerTodosRegistrosFixos(f);
    }

    return lerTodosRegistrosVariaveis(f);
}