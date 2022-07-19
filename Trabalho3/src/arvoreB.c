#include <arvoreB.h>
#include <string.h>

/*
 * Escreve no arquivo as informações default do registro de cabeçalho da árvore B.
 */
void criarRegistroCabecalho(FILE *f, char *tipoArquivo) {
    int tamLixo;
    int aux;

    (!strcmp(tipoArquivo, "tipo1")) ? (tamLixo = 32) : (tamLixo = 44);

    char *lixo = malloc(sizeof(char) * tamLixo);
    memset(lixo, '$', tamLixo);

    fwrite("0", sizeof(char), 1, f); // Status

    aux = -1;
    fwrite(&aux, sizeof(int), 1, f); // No raiz

    aux = 0;
    fwrite(&aux, sizeof(int), 1, f); // Proximo RRN
    fwrite(&aux, sizeof(int), 1, f); // Numero de nos

    fwrite(lixo, sizeof(char), tamLixo, f);
    
    free(lixo);
}

/*
 * Escreve no registro de cabeçalho o nó raiz da árvore
 */
void setNoRaiz(FILE *f, int noRaiz) {
    fseek(f, POS_NO_RAIZ, SEEK_SET);
    fwrite(&noRaiz, sizeof(int), 1, f);
}

/*
 * Faz a leitura do nó raiz da árvore no registro de cabeçalho
 */
int getNoRaiz(FILE *f) {
    int noRaiz;
    fseek(f, POS_NO_RAIZ, SEEK_SET);
    fread(&noRaiz, sizeof(int), 1, f);
    return noRaiz;
}

/*
 * Escreve no registro de cabeçalho o próximo RRN da árvore
 */
void setProxRRNArvore(FILE *f, int proxRRN) {
    fseek(f, POS_PROX_RRN, SEEK_SET);
    fwrite(&proxRRN, sizeof(int), 1, f);
}

/*
 * Faz a leitura do próximo RRN da árvore no registro de cabeçalho
 */
int getProxRRNArvore(FILE *f) {
    int proxRRN;
    fseek(f, POS_PROX_RRN, SEEK_SET);
    fread(&proxRRN, sizeof(int), 1, f);
    return proxRRN;
}

/*
 * Escreve no registro de cabeçalho o número de nós da árvore
 */
void setNumNos(FILE *f, int numNos) {
    fseek(f, POS_NUM_NOS, SEEK_SET);
    fwrite(&numNos, sizeof(int), 1, f);
}

/*
 * Faz a leitura do número de nós da árvore no registro de cabeçalho
 */
int getNumNos(FILE *f) {
    int numNos;
    fseek(f, POS_NUM_NOS, SEEK_SET);
    fread(&numNos, sizeof(int), 1, f);
    return numNos;
}

/*
 * Faz a leitura de uma determinada página de disco no arquivo de índices
 * Retorna a página de disco lida
 */
pagina lerPaginaDisco(FILE *f, char *tipoArquivo, int RRN) {
    // Verifica o tipo de indice, obtendo o tamanho do cabeçalho e, consequentemente, da página
    // OBS: tamCabecalho = tamPaginaDisco
    int tamanhoCabecalho = (!strcmp(tipoArquivo, "tipo1")) ? TAM_NO_FIXO : TAM_NO_VARIAVEL;
    fseek(f, tamanhoCabecalho + (RRN * tamanhoCabecalho), SEEK_SET);

    pagina p;

    // Leitura das informações sobre a página
    fread(&p.tipoNo, sizeof(char), 1, f);
    fread(&p.numChaves, sizeof(int), 1, f);

    // Leitura das chaves e posições relativas em relação ao arquivo de dados
    for (int i = 0; i < ORDEM_ARVORE_B - 1; i++) {
        fread(&p.chaves[i][0], sizeof(int), 1, f);

        if (!strcmp(tipoArquivo, "tipo1")) {
            fread(&p.chaves[i][1], sizeof(int), 1, f);
        } else {
            fread(&p.chaves[i][1], sizeof(long long int), 1, f);
        }
    }

    // Leitura dos ponteiros para os filhos
    for (int i = 0; i < ORDEM_ARVORE_B; i++) {
        fread(&p.filhos[i], sizeof(int), 1, f);
    }

    // printf("%c %d\n", p.tipoNo, p.numChaves);
    // for (int i = 0; i < ORDEM_ARVORE_B - 1; i++) {
    //     printf("%d %d\n", (int) p.chaves[i][0], (int) p.chaves[i][1]);
    // }
    // for (int i = 0; i < ORDEM_ARVORE_B; i++) {
    //     printf("%d\n", p.filhos[i]);
    // }

    return p;
}

/*
 * Algoritmo de busca na árvore B
 */
void buscaArvoreB(FILE *f, char *tipoArquivo, int RRN, int chave, int *paginaEncontrada_RRN, int *posChaveNaPagina) {
    if (RRN == -1) { // Condição de parada da busca, não encontrou a chave
        *paginaEncontrada_RRN = -1;
        *posChaveNaPagina = -1;
        return;
    }

    pagina p = lerPaginaDisco(f, tipoArquivo, RRN);

    int i = 0;
    while (i < p.numChaves && chave > (int) p.chaves[i][0]) { // Busca a chave na página
        i++;
    }
    // Chave encontrada
    if (i < p.numChaves && chave == (int) p.chaves[i][0]) {
        *paginaEncontrada_RRN = RRN;
        *posChaveNaPagina = i;
        return;
    }

    buscaArvoreB(f, tipoArquivo, p.filhos[i], chave, paginaEncontrada_RRN, posChaveNaPagina);
}