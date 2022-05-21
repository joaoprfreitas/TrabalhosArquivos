/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <regTamanhoVariavel.h>

#define TAM_CAMPO_FIXO 27

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
    r.topo = 0;

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

void addRegistroVariavel(FILE *f, regVariavel r) {
    fwrite(&r.removido, sizeof(char), 1, f);
    fwrite(&r.tamanhoRegistro, sizeof(int), 1, f);
    fwrite(&r.prox, sizeof(long long int), 1, f);

    fwrite(&r.id, sizeof(int), 1, f);
    fwrite(&r.ano, sizeof(int), 1, f);
    fwrite(&r.qtt, sizeof(int), 1, f);

    fwrite(&r.sigla, sizeof(char), TAM_SIGLA, f);


    // verificar se ta escrevendo ou nao
    fwrite(&r.tamCidade, sizeof(int), 1, f);
    fwrite(&r.codC5, sizeof(char), 1, f);
    fwrite(&r.cidade, sizeof(char), r.tamCidade, f);

    fwrite(&r.tamMarca, sizeof(int), 1, f);
    fwrite(&r.codC6, sizeof(char), 1, f);
    fwrite(&r.marca, sizeof(char), r.tamMarca, f);

    fwrite(&r.tamModelo, sizeof(int), 1, f);
    fwrite(&r.codC7, sizeof(char), 1, f);
    fwrite(&r.modelo, sizeof(char), r.tamModelo, f);
}

regVariavel formatRegistroVariavel(data_t *data) {
    regVariavel r;

    r.removido = '0';

    r.prox = -1;

    r.id = data->id;
    r.ano = data->ano;
    r.qtt = data->qtt;
    strcpy(r.sigla, data->sigla);

    int contadorAux = 0;
    if (strcmp(data->cidade, "")) { // Se não for vazio
        r.tamCidade = strlen(data->cidade);
        r.codC5 = '0';
        r.cidade = strdup(data->cidade);
        contadorAux += sizeof(int) + sizeof(char) + r.tamCidade;
    }
    if (strcmp(data->marca, "")) { // Se não for vazio
        r.tamMarca = strlen(data->marca);
        r.codC6 = '1';
        r.marca = strdup(data->marca);
        contadorAux += sizeof(int) + sizeof(char) + r.tamMarca;
    }
    if (strcmp(data->modelo, "")) { // Se não for vazio
        r.tamModelo = strlen(data->modelo);
        r.codC7 = '2';
        r.modelo = strdup(data->modelo);
        contadorAux += sizeof(int) + sizeof(char) + r.tamModelo;
    }

    r.tamanhoRegistro = contadorAux + TAM_CAMPO_FIXO;

    return r;
}
