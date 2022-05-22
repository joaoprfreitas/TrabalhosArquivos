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

void listarTodosRegistros(char *binFileName, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Tipo de arquivo inválido.\n");
        return;
    }

    FILE *f = openBinFile(binFileName);
    
    if (f == NULL) return;


    if (lerTodosRegistros(f, tipoArquivo) == -1)
        printf("Registro inexistente.\n");

    fclose(f);
}