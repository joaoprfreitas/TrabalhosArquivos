#include <funcionalidades.h>

void createTable(char *fileName, char *tipoArquivo, char *csvFileName) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Tipo de arquivo inválido.\n");
        return;
    }

    FILE *file = createFile(fileName);

    setRegistroCabecalho(file, tipoArquivo);

    setFileData(file, tipoArquivo, csvFileName);

    changeStatusToSafe(file);

    fclose(file);
}