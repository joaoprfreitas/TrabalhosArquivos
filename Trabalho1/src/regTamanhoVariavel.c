/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <regTamanhoVariavel.h>

#define TAM_CAMPO_FIXO 22 // desconsiderando os campos removido e tamanho do registro
#define POS_CABECALHO_PROXIMO_BYTE_OFFSET 178

long long int proxByteOffSet = 0;

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

    proxByteOffSet = ftell(f);

    fseek(f, POS_CABECALHO_PROXIMO_BYTE_OFFSET, SEEK_SET);
    fwrite(&proxByteOffSet, sizeof(long long int), 1, f);
    fseek(f, proxByteOffSet, SEEK_SET);
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
