/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <regTamanhoVariavel.h>

#define TAM_CAMPO_FIXO 22 // desconsiderando os campos removido e tamanho do registro
#define POS_CABECALHO_PROXIMO_BYTE_OFFSET 178
#define TAM_CABECALHO_VARIAVEL 190

regVariavel *lerRegistroVariavel(FILE *f);
void imprimirRegistroVariavel(regVariavel *r);
void freeRegistroVariavel(regVariavel *r);

void setDefaultCabecalhoVariavel(FILE *f, regCabecalhoVariavel r) {
    fwrite(&r.status, sizeof(char), 1, f);
    fwrite(&r.topo, sizeof(long long int), 1, f);

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

    fwrite(&r.proxByteOffset, sizeof(long long int), 1, f);
    fwrite(&r.nroRegRem, sizeof(int), 1, f);
}

regCabecalhoVariavel defaultCabecalhoVariavel() {
    regCabecalhoVariavel r;

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

    r.proxByteOffset = 0;
    r.nroRegRem = 0;

    return r;
}

long long int getProxByteOffset(FILE *f) {
    long long int proxByteOffset;
    fseek(f, POS_CABECALHO_PROXIMO_BYTE_OFFSET, SEEK_SET);
    fread(&proxByteOffset, sizeof(long long int), 1, f);

    return proxByteOffset;
}

void setProxByteOffset(FILE *f, long long int proxByteOffset) {
    fseek(f, POS_CABECALHO_PROXIMO_BYTE_OFFSET, SEEK_SET);
    fwrite(&proxByteOffset, sizeof(long long int), 1, f);
}

void addRegistroVariavel(FILE *f, regVariavel *r) {
    fwrite(&r->removido, sizeof(char), 1, f);

    fwrite(&r->tamanhoRegistro, sizeof(int), 1, f);
    fwrite(&r->prox, sizeof(long long int), 1, f);

    fwrite(&r->id, sizeof(int), 1, f);
    fwrite(&r->ano, sizeof(int), 1, f);
    fwrite(&r->qtt, sizeof(int), 1, f);

    fwrite(r->sigla, sizeof(char), TAM_SIGLA, f);

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

    fseek(f, 0, SEEK_END);
}

regVariavel formatRegistroVariavel(data_t *data) {
    regVariavel r;

    r.removido = '0';

    r.prox = -1;

    r.id = data->id;
    r.ano = data->ano;
    r.qtt = data->qtt;

    r.sigla[0] = data->sigla[0];
    r.sigla[1] = data->sigla[1];

    int contadorAux = 0;

    r.codC5 = '0';
    r.cidade = strdup(data->cidade);
    if (strcmp(data->cidade, "")) { // Se não for vazio
        r.tamCidade = strlen(data->cidade);
        contadorAux += sizeof(int) + sizeof(char) + r.tamCidade;
    } else {
        r.tamCidade = -1;
    }

    r.codC6 = '1';
    r.marca = strdup(data->marca);
    if (strcmp(data->marca, "")) { // Se não for vazio
        r.tamMarca = strlen(data->marca);
        contadorAux += sizeof(int) + sizeof(char) + r.tamMarca;
    } else {
        r.tamMarca = -1;
    }

    r.codC7 = '2';
    r.modelo = strdup(data->modelo);
    if (strcmp(data->modelo, "")) { // Se não for vazio
        r.tamModelo = strlen(data->modelo);
        contadorAux += sizeof(int) + sizeof(char) + r.tamModelo;
    } else {
        r.tamModelo = -1;
    }

    r.tamanhoRegistro = contadorAux + TAM_CAMPO_FIXO;

    return r;
}

int lerTodosRegistrosVariaveis(FILE *f) {
    int proxByteOffSet = getProxByteOffset(f);
    if (proxByteOffSet == 0) return -1;

    fseek(f, TAM_CABECALHO_VARIAVEL, SEEK_SET);

    do {

        regVariavel *r = lerRegistroVariavel(f);
        imprimirRegistroVariavel(r);
        freeRegistroVariavel(r);

    } while(proxByteOffSet != ftell(f));

    return 0;
}

regVariavel *lerRegistroVariavel(FILE *f) {
    regVariavel *r = malloc(sizeof(regVariavel));

    fread(&r->removido, sizeof(char), 1, f);
    fread(&r->tamanhoRegistro, sizeof(int), 1, f);

    fread(&r->prox, sizeof(long long int), 1, f);
    fread(&r->id, sizeof(int), 1, f);
    fread(&r->ano, sizeof(int), 1, f);
    fread(&r->qtt, sizeof(int), 1, f);
    fread(r->sigla, sizeof(char), TAM_SIGLA, f);

    r->tamCidade = -1;
    r->tamMarca = -1;
    r->tamModelo = -1;

    int contadorAux = TAM_CAMPO_FIXO;
    while (r->tamanhoRegistro > contadorAux) {
        int tamanhoAux;
        char codigoAux;

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

        contadorAux += sizeof(int) + sizeof(char) + tamanhoAux;
    }

    return r;
}

void imprimirRegistroVariavel(regVariavel *r) {
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

void freeRegistroVariavel(regVariavel *r) {
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