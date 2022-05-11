/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */
#include <file.h>

FILE *createTable(char *fileName, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Tipo de arquivo inválido.\n");
        return NULL;
    }

    FILE *f = createFile(fileName);

    setRegistroCabecalho(f, tipoArquivo);


    return f;
}

// TODO: QUANDO FOR FECHAR O ARQUIVO, SETAR NO STATUS NO ARQUIVO PARA '1'
void setRegistroCabecalho(FILE *f, char *tipoArquivo) {
    // Seta tipo 1
    if (!(strcmp(tipoArquivo, "tipo1"))) {
        setDefaultCabecalhoFixo(f, defaultCabecalhoFixo());
        return;
    }

    // Seta tipo 2
    setDefaultCabecalhoVariavel(f, defaultCabecalhoVariavel());
    
}

FILE *createFile(char *fileName) {
    FILE *f = fopen(fileName, "wb");
    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return f;
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