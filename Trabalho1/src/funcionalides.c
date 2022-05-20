#include <funcionalidades.h>

void createTable(char *fileName, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Tipo de arquivo inválido.\n");
        return NULL;
    }

    FILE *file = createFile(fileName);

    setRegistroCabecalho(file, tipoArquivo);

    // preenche csv

    fclose(file);
}