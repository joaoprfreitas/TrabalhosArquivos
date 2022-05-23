#include <funcionalidades.h>

void createTable(char *fileName, char *tipoArquivo, char *csvFileName) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Falha no processamento do arquivo.\n");
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
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = openBinFile(binFileName);
    
    if (f == NULL) return;

    int codigo = lerTodosRegistros(f, tipoArquivo);

    if (codigo == -1)
        printf("Registro inexistente.\n");
    else if (codigo == -2)
        printf("Falha no processamento do arquivo.\n");

    fclose(f);
}

void getRegistroFixo(char *nomeArquivoBinario, char *tipoArquivo, int RRN) {
    if (strcmp(tipoArquivo, "tipo1")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = openBinFile(nomeArquivoBinario);

    if (f == NULL) return;

    if (getStatus(f) == '0' || RRN < 0) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    if (RRN > getNumeroRegistros(f)) {
        printf("Registro inexistente.\n");
        return;
    }

    regFixo *r = lerRegistroFixo(f, RRN);
    imprimirRegistroFixo(r);
    freeRegistroFixo(r);

    fclose(f);
}