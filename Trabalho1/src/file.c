/*
 * SSC0215 - 2022 - Organização de arquivos
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
        if (!readLineCSV(csv, &data)) { // Chegou no fim do arquivo
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

    setProxByteOffset(file, ftell(file)); // Atualiza o cabeçalho

    fclose(csv);
}

/*
 * Abre um arquivo binário com o nome passado como parâmetro.
 * Retorna um ponteiro para o arquivo criado ou NULL no caso de um problema na abertura.
 */
FILE *abrirArquivoDados(char *fileName) {
    FILE *f = fopen(fileName, "rb+");

    if (f == NULL) return NULL;

    return f;
}

/*
 * Faz a alteração do status no registro de cabeçalho para consistente
 */
void setStatusConsistente(FILE *f) {
    fseek(f, 0, SEEK_SET);
    char status = '1';
    fwrite(&status, sizeof(char), 1, f);
}

/*
 * Faz a alteração do status no registro de cabeçalho para inconsistente
 */
void setStatusInconsistente(FILE *f) {
    fseek(f, 0, SEEK_SET);
    char status = '0';
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

/*
 * Realiza uma busca sequencial no arquivo de dados por registros que contenham determinados campos.
 * Realiza a impressão desses registros caso existam, ou imprime uma mensagem de erro caso não existam.
 */
void buscarRegistroPorCampos(FILE *f, char *tipoArquivo, campos* n_campos, int numCampos) {
    bool achou = false;
    if (getStatus(f) == '0'){   //Verifica a consistencia do arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    if (!strcmp("tipo1", tipoArquivo)) { // Registros de tamanho fixo
        int total_rrn = getNumeroRegistros(f);

        if (total_rrn == 0) { // Nenhum registro no arquivo
            printf("Registro inexistente.\n");
            return;
        }
        
        for (int i = 0; i < total_rrn; i++) { // Percorre todos os RRNs do arquivo de dados
            regFixo *r = lerRegistroFixo(f, i);

            if (verificaCamposFixos(r, n_campos, numCampos) == 0) { // Se der match
                imprimirRegistroFixo(r);
                achou = true;
            }

            freeRegistroFixo(r);
        }

        if (!achou) printf("Registro inexistente.\n");

        return;
    }

    // Registros de tamanho variável
    int proxByteOffSet = getProxByteOffset(f);

    if (proxByteOffSet == 0) {
        printf("Registro inexistente.\n");
        return;
    }
    
    regVariavel *r;

    fseek(f, TAM_CABECALHO_VARIAVEL, SEEK_SET); // Posiciona o ponteiro para o primeiro registro

    do { // Percorre todos os registros do arquivo de dados
        r = lerRegistroVariavel(f);

        if (verificaCamposVariaveis(r, n_campos, numCampos) == 0) { // Se der match
            imprimirRegistroVariavel(r); 
            achou = true;
        }

        freeRegistroVariavel(r);
    } while (proxByteOffSet != ftell(f));
                 
    if (!achou) printf("Registro inexistente.\n");
}

/*
 * Verifica o tipo do arquivo, chamando a função adequada
 * para realizar a indexação do arquivo.
 */
void realizarIndexacao(char *tipoArquivo, FILE *dados, FILE *index) {
    setStatusInconsistente(index); // Marca o arquivo de indices como inconsistente

    if (!strcmp(tipoArquivo, "tipo1")) { // Se for do tipo 1
        realizarIndexacaoRegFixo(dados, index);
        return;
    }
    // Caso contrário
    realizarIndexacaoRegVariavel(dados, index);
}

index_t lerArquivoIndex(char *tipoArquivo, FILE *arquivoIndex) {
    index_t index;

    // fseek(index, 1, SEEK_SET); // Posiciona o ponteiro para o primeiro index
    index.tamanho = 0;
    index.lista = NULL;

    int tamanhoPosicao = (!strcmp(tipoArquivo, "tipo1")) ? sizeof(int) : sizeof(long long int);
    int idAuxiliar;
    while (fread(&idAuxiliar, sizeof(int), 1, arquivoIndex) != 0) {
        index.lista = realloc(index.lista, (index.tamanho + 1) * sizeof(index_t));

        index.lista[index.tamanho].id = idAuxiliar;

        index.lista[index.tamanho].posicao = 0; // Inicializa a variável
        fread(&index.lista[index.tamanho].posicao, tamanhoPosicao, 1, arquivoIndex);

        index.tamanho++;
    }

    quickSortIndex(&index, 0, index.tamanho - 1);

    return index;
}

FILE *atualizarArquivoIndex(char *nomeIndex, char *tipoArquivo, index_t index) {
    FILE *novoIndex = criarArquivoBinario(nomeIndex);

    int tamanhoPosicao = (!strcmp(tipoArquivo, "tipo1")) ? sizeof(int) : sizeof(long long int);

    setStatusConsistente(novoIndex);

    for (int i = 0; i < index.tamanho; i++) {
        fwrite(&index.lista[i].id, sizeof(int), 1, novoIndex);
        fwrite(&index.lista[i].posicao, tamanhoPosicao, 1, novoIndex);
    }

    return novoIndex;
}

void inserirNoIndex(index_t *index, int id, long long int posicao) {
    index->lista = realloc(index->lista, (index->tamanho + 1) * sizeof(index_t));

    index->lista[index->tamanho].id = id;
    index->lista[index->tamanho].posicao = posicao;

    index->tamanho = index->tamanho + 1;

    quickSortIndex(index, 0, index->tamanho - 1);
}

topo_t leituraTopoRegVariavel(FILE *arquivoDados) {
    topo_t lista;
    lista.tamanhoLista = getNumRegRemovidosVariavel(arquivoDados);
    lista.lista = malloc(lista.tamanhoLista * sizeof(campoTopo_t));

    fseek(arquivoDados, CABECALHO_TOPO, SEEK_SET);
    
    for (int i = 0; i < lista.tamanhoLista; i++) {
        fread(&lista.lista[i].topo, sizeof(long long int), 1, arquivoDados); // Lê o byteoffset
        fseek(arquivoDados, lista.lista[i].topo, SEEK_SET); // Vai para o byteoffset
        char removido;
        fread(&removido, sizeof(char), 1, arquivoDados);
        if (removido == '1') { // Verifica se está removido
            fread(&lista.lista[i].tamanho, sizeof(int), 1, arquivoDados); // Lê o tamanho do registro
        }
    }

    return lista;
}

void atualizarListaTopo(FILE *arquivoDados, topo_t lista) {
    fseek(arquivoDados, CABECALHO_TOPO, SEEK_SET); // Muda a cabeça de leitura para o topo

    for (int i = 0; i < lista.tamanhoLista; i++) {
        fwrite(&lista.lista[i].topo, sizeof(long long int), 1, arquivoDados); // Escreve o topo
        fseek(arquivoDados, lista.lista[i].topo + 5, SEEK_SET); // Vai para o topo no registro
    }

    long long int valorFinal = -1;

    fwrite(&valorFinal, sizeof(long long int), 1, arquivoDados); // No topo do último registro, escreve -1
}

void realizarRemocao(char *tipoArquivo, FILE *arquivoDados, index_t *index, campos *camposNaLinha, int numCampos) {
    if (!strcmp(tipoArquivo, "tipo1")) {
        removerRegistroFixo(arquivoDados, index, camposNaLinha, numCampos);
        return;
    }

    topo_t listaTopo = leituraTopoRegVariavel(arquivoDados);

    removerRegistroVariavel(arquivoDados, &listaTopo, index, camposNaLinha, numCampos);

    atualizarListaTopo(arquivoDados, listaTopo);

    free(listaTopo.lista);
}

void realizarInsercao(char *tipoArquivo, FILE *arquivoDados, index_t *index, data_t *data) {
    if (!strcmp(tipoArquivo, "tipo1")) {
        inserirRegistroFixo(arquivoDados, index, data);
        return;
    }

    inserirRegistroVariavel(arquivoDados, index, data);
}

void realizarAtualizacao(char *tipoArquivo, FILE *arquivoDados, index_t *index, campos *camposNaLinha, int numCampos, campos *camposNovoRegistro, int numCamposNovoRegistro) {
    if (!strcmp(tipoArquivo, "tipo1")) {
        atualizarRegistroFixo(arquivoDados, index, camposNaLinha, numCampos, camposNovoRegistro, numCamposNovoRegistro);
        return;
    }

    atualizarRegistroVariavel(arquivoDados, index, camposNaLinha, numCampos, camposNovoRegistro, numCamposNovoRegistro);
}