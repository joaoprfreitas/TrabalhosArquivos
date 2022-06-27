/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <funcionalidades.h>
#include <funcoesFornecidas.h>
#include <funcoesFornecidas.h>
#include <utils.h>

/*
 * Funcionalidade 1 do trabalho.
 *
 * Cria o arquivo de dados armazenando o cabeçalho e todos os
 * os registros (de acordo com o tipo) do arquivo CSV.
 */
void createTable(char *nomeArquivo, char *tipoArquivo, char *nomeCSV) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *file = criarArquivoBinario(nomeArquivo);

    if (file == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    setRegistroCabecalho(file, tipoArquivo);

    preencherArquivoDados(file, tipoArquivo, nomeCSV);

    setStatusConsistente(file);

    fclose(file);

    binarioNaTela(nomeArquivo);
}

/*
 * Funcionalidade 2 do trabalho.
 *
 * Realiza a impressão de todos os registro os registros
 * armazenados em um determinado arquivo.
 */
void listarTodosRegistros(char *nomeArquivo, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);
    
    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    int codigo = lerTodosRegistros(f, tipoArquivo);

    if (codigo == -1)
        printf("Registro inexistente.\n");
    else if (codigo == -2)
        printf("Falha no processamento do arquivo.\n");

    fclose(f);
}

/*
 * Funcionalidade 3 do trabalho.
 *
 * Realiza a impressão dos registros pesquisados pelo campo.
 */
void listarCamposPesquisados(char* nomeArquivo, campos* n_campos, int numCampos, char* tipoArquivo){
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) { // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    buscarRegistroPorCampos(f, tipoArquivo, n_campos, numCampos);

    fclose(f);
}


/*
 * Funcionalidade 4 do trabalho.
 *
 * Realiza a impressão de um determinado registro fixo do arquivo
 * a partir de um dado RRN
 */
void getRegistroFixo(char *nomeArquivo, char *tipoArquivo, int RRN) {
    if (strcmp(tipoArquivo, "tipo1")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(f) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(f);
        return;
    }
    
    if (RRN > getNumeroRegistros(f) || RRN < 0) { // Verifica se o RRN é válido
        printf("Registro inexistente.\n");
        fclose(f);
        return;
    }

    regFixo *r = lerRegistroFixo(f, RRN);

    if (r->removido == '0') // Se o registro não estiver marcado como removido
        imprimirRegistroFixo(r);
    else
        printf("Registro inexistente.\n");
        
    freeRegistroFixo(r);

    fclose(f);
}

/*
 * Funcionalidade 5 do trabalho.
 *
 * Cria o arquivo de indices de um determinado arquivos de dados.
 */
void criarIndex(char *tipoArquivo, char *arquivoDados, char *arquivoIndice) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *dados = abrirArquivoDados(arquivoDados);
    FILE *index = criarArquivoBinario(arquivoIndice);

    if (dados == NULL || index == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(dados) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(dados);
        return;
    }

    realizarIndexacao(tipoArquivo, dados, index);

    setStatusConsistente(index); // Marca o arquivo como consistente

    fclose(dados);
    fclose(index);

    binarioNaTela(arquivoIndice);
}

/*
 * Funcionalidade 6 do trabalho.
 *
 * Realiza a remoção de determinados registros com base nos campos desejados.
 */
void removerRegistros(char *tipoArquivo, char *nomeArquivoDados, char *nomeArquivoIndice, campos **camposBuscados, int *numCamposPorLinha, int numLinhas) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *arquivoDados = abrirArquivoDados(nomeArquivoDados);
    
    if (arquivoDados == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    if (getStatus(arquivoDados) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoDados);
        return;
    }

    FILE *arquivoIndex = abrirArquivoDados(nomeArquivoIndice);

    if (arquivoIndex == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(arquivoIndex) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoIndex);
        return;
    }

    // Altera o status dos arquivos para inconsistentes
    setStatusInconsistente(arquivoDados);
    setStatusInconsistente(arquivoIndex);

    index_t index = lerArquivoIndex(tipoArquivo, arquivoIndex);

    fclose(arquivoIndex);
    
    // Para cada linha da entrada, realiza a remoção
    for (int i = 0; i < numLinhas; i++) {
        realizarRemocao(tipoArquivo, arquivoDados, &index, camposBuscados[i], numCamposPorLinha[i]);
    }
    
    // Atualiza o arquivo de índices
    arquivoIndex = atualizarArquivoIndex(nomeArquivoIndice, tipoArquivo, index);

    free(index.lista); // Libera a memória alocada para o vetor de indices
    
    setStatusConsistente(arquivoDados); // Marca o arquivo de dados como consistente

    fclose(arquivoDados);
    fclose(arquivoIndex);

    binarioNaTela(nomeArquivoDados);
    binarioNaTela(nomeArquivoIndice);
}

/*
 * Funcionalidade 7 do trabalho.
 *
 * Realiza a inserção de novos registros no arquivo de dados.
 */
void insereRegistros(char* tipoArquivo, char *nomeArquivoDados, char *nomeArquivoIndice, data_t *data, int numRegistros) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *arquivoDados = abrirArquivoDados(nomeArquivoDados);
    
    if (arquivoDados == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    if (getStatus(arquivoDados) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoDados);
        return;
    }

    FILE *arquivoIndex = abrirArquivoDados(nomeArquivoIndice);

    if (arquivoIndex == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(arquivoIndex) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoIndex);
        return;
    }

    // Altera o status dos arquivos para inconsistentes
    setStatusInconsistente(arquivoDados);
    setStatusInconsistente(arquivoIndex);

    // Faz a leitura do arquivo de índices
    index_t index = lerArquivoIndex(tipoArquivo, arquivoIndex);

    fclose(arquivoIndex);

    // Realiza a inserção para cada registro
    for (int i = 0; i < numRegistros; i++) {
        realizarInsercao(tipoArquivo, arquivoDados, &index, &data[i]);
    }

    // Atualiza o arquivo de índices
    arquivoIndex = atualizarArquivoIndex(nomeArquivoIndice, tipoArquivo, index);

    free(index.lista); // Libera a memória alocada para o vetor de indices
    
    setStatusConsistente(arquivoDados); // Marca o arquivo de dados como consistente

    fclose(arquivoDados);
    fclose(arquivoIndex);

    binarioNaTela(nomeArquivoDados);
    binarioNaTela(nomeArquivoIndice);
}

/*
 * Funcionalidade 8 do trabalho.
 *
 * Realiza a atualização de registros existentes no arquivo de dados.
 */
void atualizarRegistros(char *tipoArquivo, char *nomeArquivoDados, char *nomeArquivoIndice, campos **camposBuscados, int *numCamposPorLinha, campos **novosValores, int *numCamposPorLinhaNovosValores, int numLinhas) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) { // Verifica se o tipo é válido
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *arquivoDados = abrirArquivoDados(nomeArquivoDados);
    
    if (arquivoDados == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    if (getStatus(arquivoDados) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoDados);
        return;
    }

    FILE *arquivoIndex = abrirArquivoDados(nomeArquivoIndice);

    if (arquivoIndex == NULL) {  // Problema ao abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(arquivoIndex) == '0') { // Arquivo inconsistente
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoIndex);
        return;
    }

    // Altera o status dos arquivos para inconsistentes
    setStatusInconsistente(arquivoDados);
    setStatusInconsistente(arquivoIndex);

    index_t index = lerArquivoIndex(tipoArquivo, arquivoIndex);

    fclose(arquivoIndex);

    // Realiza a atualização para cada par de linhas da entrada
    for (int i = 0; i < numLinhas; i++) {
        realizarAtualizacao(tipoArquivo, arquivoDados, &index, camposBuscados[i], numCamposPorLinha[i], novosValores[i], numCamposPorLinhaNovosValores[i]);
    }

    // Atualiza o arquivo de índices
    arquivoIndex = atualizarArquivoIndex(nomeArquivoIndice, tipoArquivo, index);

    free(index.lista); // Libera a memória alocada para o vetor de indices
    
    setStatusConsistente(arquivoDados); // Marca o arquivo de dados como consistente

    fclose(arquivoDados);
    fclose(arquivoIndex);

    binarioNaTela(nomeArquivoDados);
    binarioNaTela(nomeArquivoIndice);
}