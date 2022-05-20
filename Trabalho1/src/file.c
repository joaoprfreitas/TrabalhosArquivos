/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#include <file.h>

// TODO: QUANDO FOR FECHAR O ARQUIVO, SETAR NO STATUS NO ARQUIVO PARA '1'
void setRegistroCabecalho(FILE *file, char *tipoArquivo) {
    // Seta tipo 1
    if (!(strcmp(tipoArquivo, "tipo1"))) {
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

void setFileData(FILE *file, char *tipoArquivo) {
    if (!(strcmp(tipoArquivo, "tipo1"))) {
        setDataRegistroFixo(file);
        return;
    }

    setDataRegistroVariavel(file);
}

void setDataRegistroFixo(FILE *file) {

}

void setDataRegistroVariavel(FILE *file) {
    
}