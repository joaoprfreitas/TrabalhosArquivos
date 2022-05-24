/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <regTamanhoFixo.h>
#include <string.h>

#define TAM_REGISTRO_FIXO 97
#define TAM_CAMPOS_FIXO 19
#define POS_CABECALHO_PROXIMO_RRN 174
#define TAM_CABECALHO 182


/*
 * Escreve  as informações do cabeçalho de um arquivo de dados
 * com registros de tamanho fixo a partir da estrutura de um
 * registro.
 */
void setCabecalhoRegistroFixo(FILE *f, regCabecalhoFixo r) {
    fwrite(&r.status, sizeof(char), 1, f);
    fwrite(&r.topo, sizeof(int), 1, f);

    fwrite(&r.descricao, sizeof(char), TAM_DESCRICAO, f);

    fwrite(&r.desC1, sizeof(char), TAM_DESC1, f);
    fwrite(&r.desC2, sizeof(char), TAM_DESC2, f);
    fwrite(&r.desC3, sizeof(char), TAM_DESC3, f);
    fwrite(&r.desC4, sizeof(char), TAM_DESC4, f);

    fwrite(&r.codC5, sizeof(char), 1, f);
    fwrite(&r.desC5, sizeof(char), TAM_DESC5, f);
    fwrite(&r.codC6, sizeof(char), 1, f);
    fwrite(&r.desC6, sizeof(char), TAM_DESC6, f);
    fwrite(&r.codC7, sizeof(char), 1, f);
    fwrite(&r.desC7, sizeof(char), TAM_DESC7, f);

    fwrite(&r.proxRRN, sizeof(int), 1, f);
    fwrite(&r.nroRegRem, sizeof(int), 1, f);
}

/*
 * Seta o cabeçalho default para um arquivo de dados
 * com regitros de tamanho fixo.
 * 
 * Retorna a estrutura do cabeçalho devidamente preenchida.
 */
regCabecalhoFixo defaultCabecalhoFixo() {
    regCabecalhoFixo r;

    r.status = '0';
    r.topo = -1;
    
    strcpy(r.descricao, "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL");
    strcpy(r.desC1, "CODIGO IDENTIFICADOR: ");
    strcpy(r.desC2, "ANO DE FABRICACAO: ");
    strcpy(r.desC3, "QUANTIDADE DE VEICULOS: ");
    strcpy(r.desC4, "ESTADO: ");

    r.codC5 = '0';
    strcpy(r.desC5, "NOME DA CIDADE: ");
    r.codC6 = '1';
    strcpy(r.desC6, "MARCA DO VEICULO: ");
    r.codC7 = '2';
    strcpy(r.desC7, "MODELO DO VEICULO: ");

    r.proxRRN = 0;
    r.nroRegRem = 0;

    return r;
}

/*
 * Retorna próximo RRN livre segundo o cabeçalho do arquivo de dados.
 */
int getProxRRN(FILE *f) {
    int proxRRN;

    fseek(f, POS_CABECALHO_PROXIMO_RRN, SEEK_SET);
    fread(&proxRRN, sizeof(int), 1, f);

    return proxRRN;
}

/*
 * Seta um valor qualquer para o campo proxRRN
 * no registro de cabeçalho do arquivo de dados.
 */
void setProxRRN(FILE *f, int proxRRN) {
    fseek(f, POS_CABECALHO_PROXIMO_RRN, SEEK_SET);
    fwrite(&proxRRN, sizeof(int), 1, f);
}

/*
 * Incrementa em 1 o campo proxRRN no cabeçalho do arquivo de dados.
 */
void addProxRRN(FILE *f) {
    int proxRRN = getProxRRN(f) + 1;
    fseek(f, POS_CABECALHO_PROXIMO_RRN, SEEK_SET);
    fwrite(&proxRRN, sizeof(int), 1, f);
}

/*
 * Adiciona um registro de tamanho fixo no fim do arquivo de dados.
 * Para isto, é passada a estrutura do registro devidamente preenchida.
 * Ainda, a função faz as verificações a respeito da cidade, marca e modelo,
 * inserindo no arquivo essas informações caso existam.
 * Por fim, preenche o restante do espaço do registro com lixo ('$').
 */
void addRegistroFixo(FILE *f, regFixo *r) {
    fwrite(&r->removido, sizeof(char), 1, f);
    fwrite(&r->prox, sizeof(int), 1, f);

    fwrite(&r->id, sizeof(int), 1, f);
    fwrite(&r->ano, sizeof(int), 1, f);
    fwrite(&r->qtt, sizeof(int), 1, f);
    
    fwrite(r->sigla, sizeof(char), 2, f);

    if (r->tamCidade != -1) {
        fwrite(&r->tamCidade, sizeof(int), 1, f);
        fwrite(&r->codC5, sizeof(char), 1, f);
        fwrite(r->cidade, sizeof(char), r->tamCidade, f);
    }

    if (r->tamMarca != -1) {
        fwrite(&r->tamMarca, sizeof(int), 1, f);
        fwrite(&r->codC6, sizeof(char), 1, f);
        fwrite(r->marca, sizeof(char), r->tamMarca, f);
    }

    if (r->tamModelo != -1) {
        fwrite(&r->tamModelo, sizeof(int), 1, f);
        fwrite(&r->codC7, sizeof(char), 1, f);
        fwrite(r->modelo, sizeof(char), r->tamModelo, f);
    }

    char *lixo = malloc(sizeof(char) * r->tamLixo);
    memset(lixo, '$', r->tamLixo); // Preenche todas as posições do lixo com '$'
    fwrite(lixo, sizeof(char), r->tamLixo, f);

    free(lixo);
}

/*
 * Realiza o parsing dos dados lidos de uma linha do CSV para
 * uma estrutura do registro de tamanho fixo.
 * 
 * Seta os campos removido e prox com valores default ('0' e -1, respectivamente).
 * Faz as cópias dos dados lidos para as variáveis do registro.
 * Caso algum campo do CSV não exista, o tamanho do campo variável é setado para -1.
 * 
 * Por fim, retorna a estrutura do registro devidamente preenchida.
 */
regFixo formatRegistroFixo(data_t *data) {
    regFixo r;
    
    r.removido = '0';
    r.prox = -1;

    r.id = data->id;
    r.ano = data->ano;
    r.qtt = data->qtt;

    r.sigla[0] = data->sigla[0];
    r.sigla[1] = data->sigla[1];

    int tamanhoCamposVariaveis = 0;

    r.codC5 = '0';
    r.cidade = strdup(data->cidade);
    if (strcmp(data->cidade, "")) {  // Se não for vazio
        r.tamCidade = strlen(data->cidade);
        tamanhoCamposVariaveis += sizeof(int) + sizeof(char) + r.tamCidade;
    } else {
        r.tamCidade = -1;
    }

    r.codC6 = '1';
    r.marca = strdup(data->marca);
    if (strcmp(data->marca, "")) {  // Se não for vazio
        r.tamMarca = strlen(data->marca);
        tamanhoCamposVariaveis += sizeof(int) + sizeof(char) + r.tamMarca;
    } else {
        r.tamMarca = -1;
    }

    r.codC7 = '2';
    r.modelo = strdup(data->modelo);
    if (strcmp(data->modelo, "")) {  // Se não for vazio
        r.tamModelo = strlen(data->modelo);
        tamanhoCamposVariaveis += sizeof(int) + sizeof(char) + r.tamModelo;
    } else {
        r.tamModelo = -1;
    }

    r.tamLixo = TAM_REGISTRO_FIXO - TAM_CAMPOS_FIXO - tamanhoCamposVariaveis;
    
    return r;
}

/*
 * Retorna o número de registros no arquivo de dados.
 */
int getNumeroRegistros(FILE *f) {
    return getProxRRN(f) - 1;
}

/*
 * Faz a leitura completa dos registros do arquivo de dados.
 * Para cada registro:
 *  - Realiza a impressão dos dados de cada registro (caso não esteja removido logicamente).
 *  - Libera a memória auxiliar utilizada para armazenar temporariamente o registro impresso.
 * 
 * Retorna:
 *  - 0 caso a leitura tenha sido bem sucedida
 *  - -1 caso não existam registros armazenados.
 */
int lerTodosRegistrosFixos(FILE *f) {
    int numTotalRRN = getNumeroRegistros(f);

    if (numTotalRRN == 0) return -1;

    for (int i = 0; i <= numTotalRRN; i++) {
        regFixo *r = lerRegistroFixo(f, i);

        if (r->removido == '0') imprimirRegistroFixo(r);

        freeRegistroFixo(r);
    }

    return 0;
}

/*
 * Faz a leitura de um determinado registro no arquivo de dados a
 * partir de um determinado RRN.
 * 
 * Aloca a estrutura do registro;
 * Faz a leitura das informações do registro no arquivo de dados, armazenando na estrutura alocada;
 * Faz as verificações de existência ou não dos campos variáveis do registro
 * 
 * Retorna a estrutura do registro fixo preenchida.
 */
regFixo *lerRegistroFixo(FILE *f, int RRN) {
    regFixo *r = malloc(sizeof(regFixo));
    fseek(f, TAM_CABECALHO + (TAM_REGISTRO_FIXO * RRN), SEEK_SET);

    fread(&r->removido, sizeof(char), 1, f);
    fread(&r->prox, sizeof(int), 1, f);
    fread(&r->id, sizeof(int), 1, f);
    fread(&r->ano, sizeof(int), 1, f);
    fread(&r->qtt, sizeof(int), 1, f);
    fread(r->sigla, sizeof(char), 2, f);

    char testeExistencia[4];
    int tamanhoAux;
    char codigoAux;

    // Faz as verificações de existência ou não dos campos cidade, marca e modelo
    
    r->tamCidade = -1;
    r->tamMarca = -1;
    r->tamModelo = -1;
    
    for (int i = 0; i < 3; i++) {
        fread(&testeExistencia, sizeof(char), 4, f);

        if (strcmp(testeExistencia, "$$$$") == 0) { // Se não existir nada
            break;
        }

        
        fseek(f, -4, SEEK_CUR);

        fread(&tamanhoAux, sizeof(int), 1, f);
        fread(&codigoAux, sizeof(char), 1, f);

        switch (codigoAux) {
            case '0':
                r->tamCidade = tamanhoAux;
                r->codC5 = codigoAux;
                r->cidade = malloc(sizeof(char) * (r->tamCidade + 1));

                fread(r->cidade, sizeof(char), r->tamCidade, f);
                r->cidade[r->tamCidade] = '\0';
                break;

            case '1':
                r->tamMarca = tamanhoAux;
                r->codC6 = codigoAux;
                r->marca = malloc(sizeof(char) * (r->tamMarca + 1));

                fread(r->marca, sizeof(char), r->tamMarca, f);
                r->marca[r->tamMarca] = '\0';
                break;
            
            case '2':
                r->tamModelo = tamanhoAux;
                r->codC7 = codigoAux;
                r->modelo = malloc(sizeof(char) * (r->tamModelo + 1));

                fread(r->modelo, sizeof(char), r->tamModelo, f);
                r->modelo[r->tamModelo] = '\0';
                break;
            
            default:
                break;
        }
    }

    return r;
}


/*
 * Faz a impressão dos dados de um determinado registro fixo
 * caso não esteja marcado como logicamente removido.
 * Caso um determinado campo não exista, imprime "NAO PREENCHIDO"
 */
void imprimirRegistroFixo(regFixo *r) {
    if (r->removido == '1') return;
    
    if (r->tamMarca == -1) {
        printf("MARCA DO VEICULO: NAO PREENCHIDO\n");
    } else {
        printf("MARCA DO VEICULO: %s\n", r->marca);
    }

    if (r->tamModelo == -1) {
        printf("MODELO DO VEICULO: NAO PREENCHIDO\n");
    } else {
        printf("MODELO DO VEICULO: %s\n", r->modelo);
    }

    if (r->ano == -1) {
        printf("ANO DE FABRICACAO: NAO PREENCHIDO\n");
    } else {
        printf("ANO DE FABRICACAO: %d\n", r->ano);
    }

    if (r->tamCidade == -1) {
        printf("NOME DA CIDADE: NAO PREENCHIDO\n");
    } else {
        printf("NOME DA CIDADE: %s\n", r->cidade);
    }

    if (r->qtt == -1) {
        printf("QUANTIDADE DE VEICULOS: NAO PREENCHIDO\n");
    } else {
        printf("QUANTIDADE DE VEICULOS: %d\n", r->qtt);
    }

    printf("\n");
}

/*
 * Libera os espaços alocados para os campos variáveis
 * e o do próprio registro.
 */
void freeRegistroFixo(regFixo *r) {
    if (r->tamMarca != -1) {
        free(r->marca);
    }
    if (r->tamModelo != -1) {
        free(r->modelo);
    }
    if (r->tamCidade != -1) {
        free(r->cidade);
    }
    free(r);
}